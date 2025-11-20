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