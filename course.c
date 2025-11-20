#include "course.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INITIAL_CAPACITY 10

static int next_course_id = 1;

CourseList* course_list_create() {
    CourseList *list = (CourseList*)malloc(sizeof(CourseList));
    if (!list) return NULL;
    
    list->data = (Course*)malloc(INITIAL_CAPACITY * sizeof(Course));
    if (!list->data) {
        free(list);
        return NULL;
    }
    
    list->size = 0;
    list->capacity = INITIAL_CAPACITY;
    return list;
}

void course_list_free(CourseList *list) {
    if (list) {
        free(list->data);
        free(list);
    }
}

static int course_list_resize(CourseList *list) {
    int new_capacity = list->capacity * 2;
    Course *new_data = (Course*)realloc(list->data, new_capacity * sizeof(Course));
    if (new_data) {
        list->data = new_data;
        list->capacity = new_capacity;
        return 1;
    }
    return 0;
}
int course_list_add(CourseList *list, const char *name, int credits) {
    if (!list || !name) return -1;
    
    if (list->size >= list->capacity) {
        if (!course_list_resize(list)) {
            return -1;
        }
    }
    
    Course *course = &list->data[list->size];
    course->id = next_course_id++;
    strncpy(course->name, name, MAX_COURSE_NAME_LENGTH - 1);
    course->name[MAX_COURSE_NAME_LENGTH - 1] = '\0';
    course->credits = credits;
    
    list->size++;
    return course->id;
}

int course_list_remove(CourseList *list, int id) {
    if (!list) return 0;
    
    for (int i = 0; i < list->size; i++) {
        if (list->data[i].id == id) {
            for (int j = i; j < list->size - 1; j++) {
                list->data[j] = list->data[j + 1];
            }
            list->size--;
            return 1;
        }
    }
    return 0;
}

Course* course_list_find_by_id(CourseList *list, int id) {
    if (!list) return NULL;
    
    for (int i = 0; i < list->size; i++) {
        if (list->data[i].id == id) {
            return &list->data[i];
        }
    }
    return NULL;
}

void course_list_display(CourseList *list) {
    if (!list || list->size == 0) {
        printf("\nNo hay materias registradas.\n");
        return;
    }
    
    printf("\n=== LISTA DE MATERIAS ===\n");
    printf("%-5s %-40s %-10s\n", "ID", "Nombre", "Creditos");
    printf("--------------------------------------------------------------\n");
    
    for (int i = 0; i < list->size; i++) {
        Course *c = &list->data[i];
        printf("%-5d %-40s %-10d\n", c->id, c->name, c->credits);
    }
    printf("\n");
}

int course_list_update(CourseList *list, int id, const char *new_name, int new_credits) {
    Course *course = course_list_find_by_id(list, id);
    if (!course) return 0;
    
    if (new_name) {
        strncpy(course->name, new_name, MAX_COURSE_NAME_LENGTH - 1);
        course->name[MAX_COURSE_NAME_LENGTH - 1] = '\0';
    }
    if (new_credits >= 0) {
        course->credits = new_credits;
    }
    return 1;
}