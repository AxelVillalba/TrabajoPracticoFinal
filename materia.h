#ifndef COURSE_H
#define COURSE_H

#define MAX_COURSE_NAME_LENGTH 100

typedef struct {
    int id;
    char name[MAX_COURSE_NAME_LENGTH];
    int credits;
} Course;