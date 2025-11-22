#include "student.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INITIAL_CAPACITY 10

static int next_student_id = 1;

StudentList* student_list_create() {
    StudentList *list = (StudentList*)malloc(sizeof(StudentList));
    if (!list) return NULL;
    
    list->data = (Student*)malloc(INITIAL_CAPACITY * sizeof(Student));
    if (!list->data) {
        free(list);
        return NULL;
    }
    
    list->size = 0;
    list->capacity = INITIAL_CAPACITY;
    return list;
}

void student_list_free(StudentList *list) {
    if (list) {
        free(list->data);
        free(list);
    }
}

static int student_list_resize(StudentList *list) {
    int new_capacity = list->capacity * 2;
    Student *new_data = (Student*)realloc(list->data, new_capacity * sizeof(Student));
    if (new_data) {
        list->data = new_data;
        list->capacity = new_capacity;
        return 1;
    }
    return 0;
}

int student_list_add(StudentList *list, const char *name, int age) {
    if (!list || !name) return -1;
    
    if (list->size >= list->capacity) {
        if (!student_list_resize(list)) {
            return -1;
        }
    }
    
    Student *student = &list->data[list->size];
    student->id = next_student_id++;
    strncpy(student->name, name, MAX_NAME_LENGTH - 1);
    student->name[MAX_NAME_LENGTH - 1] = '\0';
    student->age = age;
    student->enrollment_count = 0;
    
    list->size++;
    return student->id;
}

int student_list_remove(StudentList *list, int id) {
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

Student* student_list_find_by_id(StudentList *list, int id) {
    if (!list) return NULL;
    
    for (int i = 0; i < list->size; i++) {
        if (list->data[i].id == id) {
            return &list->data[i];
        }
    }
    return NULL;
}

void student_list_display(StudentList *list) {
    if (!list || list->size == 0) {
        printf("\nNo hay estudiantes registrados.\n");
        return;
    }
    
    printf("\n=== LISTA DE ESTUDIANTES ===\n");
    printf("%-5s %-30s %-5s %-15s\n", "ID", "Nombre", "Edad", "Materias");
    printf("--------------------------------------------------------------\n");
    
    for (int i = 0; i < list->size; i++) {
        Student *s = &list->data[i];
        printf("%-5d %-30s %-5d %-15d\n", s->id, s->name, s->age, s->enrollment_count);
    }
    printf("\n");
}

void student_list_search_by_name(StudentList *list, const char *query) {
    if (!list || !query) return;
    
    int found = 0;
    printf("\n=== BUSQUEDA POR NOMBRE: '%s' ===\n", query);
    printf("%-5s %-30s %-5s\n", "ID", "Nombre", "Edad");
    printf("--------------------------------------------------------------\n");
    
    for (int i = 0; i < list->size; i++) {
        if (strstr(list->data[i].name, query) != NULL) {
            Student *s = &list->data[i];
            printf("%-5d %-30s %-5d\n", s->id, s->name, s->age);
            found = 1;
        }
    }
    
    if (!found) {
        printf("No se encontraron estudiantes.\n");
    }
    printf("\n");
}

void student_list_search_by_age_range(StudentList *list, int min_age, int max_age) {
    if (!list) return;
    
    int found = 0;
    printf("\n=== BUSQUEDA POR EDAD: %d - %d ===\n", min_age, max_age);
    printf("%-5s %-30s %-5s\n", "ID", "Nombre", "Edad");
    printf("--------------------------------------------------------------\n");
    
    for (int i = 0; i < list->size; i++) {
        if (list->data[i].age >= min_age && list->data[i].age <= max_age) {
            Student *s = &list->data[i];
            printf("%-5d %-30s %-5d\n", s->id, s->name, s->age);
            found = 1;
        }
    }
    
    if (!found) {
        printf("No se encontraron estudiantes en ese rango de edad.\n");
    }
    printf("\n");
}

int student_list_update(StudentList *list, int id, const char *new_name, int new_age) {
    Student *student = student_list_find_by_id(list, id);
    if (!student) return 0;
    
    if (new_name) {
        strncpy(student->name, new_name, MAX_NAME_LENGTH - 1);
        student->name[MAX_NAME_LENGTH - 1] = '\0';
    }
    if (new_age > 0) {
        student->age = new_age;
    }
    return 1;
}

int student_enroll(Student *student, int course_id) {
    if (!student) return 0;
    
    if (student->enrollment_count >= MAX_ENROLLMENTS) {
        return 0;
    }
    
    for (int i = 0; i < student->enrollment_count; i++) {
        if (student->enrollments[i].course_id == course_id) {
            return 0;
        }
    }
    
    Enrollment *enroll = &student->enrollments[student->enrollment_count];
    enroll->course_id = course_id;
    enroll->grade = -1.0;
    enroll->has_taken_exam = 0;
    student->enrollment_count++;
    
    return 1;
}

int student_take_exam(Student *student, int course_id, float grade) {
    if (!student) return 0;
    
    for (int i = 0; i < student->enrollment_count; i++) {
        if (student->enrollments[i].course_id == course_id) {
            student->enrollments[i].grade = grade;
            student->enrollments[i].has_taken_exam = 1;
            return 1;
        }
    }
    return 0;
}

Enrollment* student_find_enrollment(Student *student, int course_id) {
    if (!student) return NULL;
    
    for (int i = 0; i < student->enrollment_count; i++) {
        if (student->enrollments[i].course_id == course_id) {
            return &student->enrollments[i];
        }
    }
    return NULL;
}
