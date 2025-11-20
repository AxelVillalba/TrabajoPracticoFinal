#ifndef COURSE_H
#define COURSE_H

#define MAX_COURSE_NAME_LENGTH 100

typedef struct {
    int id;
    char name[MAX_COURSE_NAME_LENGTH];
    int credits;
} Course;
typedef struct {
    Course *data;
    int size;
    int capacity;
} CourseList;

CourseList* course_list_create();
void course_list_free(CourseList *list);
int course_list_add(CourseList *list, const char *name, int credits);
int course_list_remove(CourseList *list, int id);
Course* course_list_find_by_id(CourseList *list, int id);
void course_list_display(CourseList *list);
int course_list_update(CourseList *list, int id, const char *new_name, int new_credits);

#endif