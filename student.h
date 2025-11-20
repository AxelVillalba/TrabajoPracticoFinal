#ifndef STUDENT_H
#define STUDENT_H

#define MAX_NAME_LENGTH 100
#define MAX_ENROLLMENTS 50

typedef struct {
    int course_id;
    float grade;
    int has_taken_exam;
} Enrollment;

typedef struct {
    int id;
    char name[MAX_NAME_LENGTH];
    int age;
    Enrollment enrollments[MAX_ENROLLMENTS];
    int enrollment_count;
} Student;
