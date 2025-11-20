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
typedef struct {
    Student *data;
    int size;
    int capacity;
} StudentList;

StudentList* student_list_create();
void student_list_free(StudentList *list);
int student_list_add(StudentList *list, const char *name, int age);
int student_list_remove(StudentList *list, int id);
Student* student_list_find_by_id(StudentList *list, int id);
void student_list_display(StudentList *list);
void student_list_search_by_name(StudentList *list, const char *query);
void student_list_search_by_age_range(StudentList *list, int min_age, int max_age);
int student_list_update(StudentList *list, int id, const char *new_name, int new_age);
int student_enroll(Student *student, int course_id);
int student_take_exam(Student *student, int course_id, float grade);
Enrollment* student_find_enrollment(Student *student, int course_id);

#endif
