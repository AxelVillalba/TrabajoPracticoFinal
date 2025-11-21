#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "student.h"
#include "course.h"

void clear_input_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void show_main_menu() {
    printf("\n");
    printf("╔════════════════════════════════════════════════════════════╗\n");
    printf("║      SISTEMA DE GESTION DE ESTUDIANTES Y MATERIAS         ║\n");
    printf("╠════════════════════════════════════════════════════════════╣\n");
    printf("║  ESTUDIANTES:                                              ║\n");
    printf("║    1. Dar de alta estudiante                               ║\n");
    printf("║    2. Modificar estudiante                                 ║\n");
    printf("║    3. Eliminar estudiante                                  ║\n");
    printf("║    4. Listar estudiantes                                   ║\n");
    printf("║    5. Buscar estudiante por nombre                         ║\n");
    printf("║    6. Buscar estudiantes por rango de edad                 ║\n");
    printf("║    7. Ver detalle de estudiante                            ║\n");
    printf("║                                                            ║\n");
    printf("║  MATERIAS:                                                 ║\n");
    printf("║    8. Dar de alta materia                                  ║\n");
    printf("║    9. Modificar materia                                    ║\n");
    printf("║   10. Eliminar materia                                     ║\n");
    printf("║   11. Listar materias                                      ║\n");
    printf("║                                                            ║\n");
    printf("║  INSCRIPCIONES Y EXAMENES:                                 ║\n");
    printf("║   12. Inscribir estudiante en materia                      ║\n");
    printf("║   13. Rendir examen                                        ║\n");
    printf("║                                                            ║\n");
    printf("║    0. Salir                                                ║\n");
    printf("╚════════════════════════════════════════════════════════════╝\n");
    printf("\nSeleccione una opcion: ");
}

void add_student(StudentList *students) {
    char name[MAX_NAME_LENGTH];
    int age;
    
    printf("\n=== ALTA DE ESTUDIANTE ===\n");
    printf("Nombre: ");
    clear_input_buffer();
    fgets(name, MAX_NAME_LENGTH, stdin);
    name[strcspn(name, "\n")] = '\0';
    
    printf("Edad: ");
    if (scanf("%d", &age) != 1 || age < 1 || age > 120) {
        printf("Error: Edad invalida.\n");
        return;
    }
    
    int id = student_list_add(students, name, age);
    if (id > 0) {
        printf("Estudiante agregado exitosamente con ID: %d\n", id);
    } else {
        printf("Error al agregar estudiante.\n");
    }
}

void update_student(StudentList *students) {
    int id;
    char name[MAX_NAME_LENGTH];
    int age;
    
    printf("\n=== MODIFICAR ESTUDIANTE ===\n");
    printf("ID del estudiante: ");
    if (scanf("%d", &id) != 1) {
        printf("Error: ID invalido.\n");
        return;
    }
    
    Student *student = student_list_find_by_id(students, id);
    if (!student) {
        printf("Error: Estudiante no encontrado.\n");
        return;
    }
    
    printf("Estudiante actual: %s (Edad: %d)\n", student->name, student->age);
    printf("Nuevo nombre (Enter para mantener): ");
    clear_input_buffer();
    fgets(name, MAX_NAME_LENGTH, stdin);
    name[strcspn(name, "\n")] = '\0';
    
    printf("Nueva edad (0 para mantener): ");
    if (scanf("%d", &age) != 1) {
        age = 0;
    }
    
    if (student_list_update(students, id, strlen(name) > 0 ? name : NULL, age)) {
        printf("Estudiante modificado exitosamente.\n");
    } else {
        printf("Error al modificar estudiante.\n");
    }
}

void delete_student(StudentList *students) {
    int id;
    
    printf("\n=== ELIMINAR ESTUDIANTE ===\n");
    printf("ID del estudiante: ");
    if (scanf("%d", &id) != 1) {
        printf("Error: ID invalido.\n");
        return;
    }
    
    Student *student = student_list_find_by_id(students, id);
    if (!student) {
        printf("Error: Estudiante no encontrado.\n");
        return;
    }
    
    printf("¿Esta seguro de eliminar a %s? (s/n): ", student->name);
    clear_input_buffer();
    char confirm = getchar();
    
    if (confirm == 's' || confirm == 'S') {
        if (student_list_remove(students, id)) {
            printf("Estudiante eliminado exitosamente.\n");
        } else {
            printf("Error al eliminar estudiante.\n");
        }
    } else {
        printf("Operacion cancelada.\n");
    }
}

void search_student_by_name(StudentList *students) {
    char query[MAX_NAME_LENGTH];
    
    printf("\n=== BUSCAR ESTUDIANTE POR NOMBRE ===\n");
    printf("Nombre a buscar: ");
    clear_input_buffer();
    fgets(query, MAX_NAME_LENGTH, stdin);
    query[strcspn(query, "\n")] = '\0';
    
    student_list_search_by_name(students, query);
}

void search_student_by_age(StudentList *students) {
    int min_age, max_age;
    
    printf("\n=== BUSCAR ESTUDIANTES POR EDAD ===\n");
    printf("Edad minima: ");
    if (scanf("%d", &min_age) != 1) {
        printf("Error: Edad invalida.\n");
        return;
    }
    
    printf("Edad maxima: ");
    if (scanf("%d", &max_age) != 1) {
        printf("Error: Edad invalida.\n");
        return;
    }
    
    student_list_search_by_age_range(students, min_age, max_age);
}

void view_student_detail(StudentList *students, CourseList *courses) {
    int id;
    
    printf("\n=== DETALLE DE ESTUDIANTE ===\n");
    printf("ID del estudiante: ");
    if (scanf("%d", &id) != 1) {
        printf("Error: ID invalido.\n");
        return;
    }
    
    Student *student = student_list_find_by_id(students, id);
    if (!student) {
        printf("Error: Estudiante no encontrado.\n");
        return;
    }
    
    printf("\nID: %d\n", student->id);
    printf("Nombre: %s\n", student->name);
    printf("Edad: %d\n", student->age);
    printf("\nMaterias inscritas (%d):\n", student->enrollment_count);
    
    if (student->enrollment_count == 0) {
        printf("  No tiene materias inscritas.\n");
    } else {
        printf("%-5s %-40s %-10s %-10s\n", "ID", "Materia", "Nota", "Estado");
        printf("----------------------------------------------------------------\n");
        
        for (int i = 0; i < student->enrollment_count; i++) {
            Enrollment *e = &student->enrollments[i];
            Course *c = course_list_find_by_id(courses, e->course_id);
            
            if (c) {
                char grade_str[10];
                char status[15];
                
                if (e->has_taken_exam) {
                    snprintf(grade_str, sizeof(grade_str), "%.2f", e->grade);
                    if (e->grade >= 4.0) {
                        strcpy(status, "Aprobado");
                    } else {
                        strcpy(status, "Desaprobado");
                    }
                } else {
                    strcpy(grade_str, "N/A");
                    strcpy(status, "Sin rendir");
                }
                
                printf("%-5d %-40s %-10s %-10s\n", c->id, c->name, grade_str, status);
            }
        }
    }
    printf("\n");
}

void add_course(CourseList *courses) {
    char name[MAX_COURSE_NAME_LENGTH];
    int credits;
    
    printf("\n=== ALTA DE MATERIA ===\n");
    printf("Nombre: ");
    clear_input_buffer();
    fgets(name, MAX_COURSE_NAME_LENGTH, stdin);
    name[strcspn(name, "\n")] = '\0';
    
    printf("Creditos: ");
    if (scanf("%d", &credits) != 1 || credits < 1) {
        printf("Error: Creditos invalidos.\n");
        return;
    }
    
    int id = course_list_add(courses, name, credits);
    if (id > 0) {
        printf("Materia agregada exitosamente con ID: %d\n", id);
    } else {
        printf("Error al agregar materia.\n");
    }
}

void update_course(CourseList *courses) {
    int id;
    char name[MAX_COURSE_NAME_LENGTH];
    int credits;
    
    printf("\n=== MODIFICAR MATERIA ===\n");
    printf("ID de la materia: ");
    if (scanf("%d", &id) != 1) {
        printf("Error: ID invalido.\n");
        return;
    }
    
    Course *course = course_list_find_by_id(courses, id);
    if (!course) {
        printf("Error: Materia no encontrada.\n");
        return;
    }
    
    printf("Materia actual: %s (Creditos: %d)\n", course->name, course->credits);
    printf("Nuevo nombre (Enter para mantener): ");
    clear_input_buffer();
    fgets(name, MAX_COURSE_NAME_LENGTH, stdin);
    name[strcspn(name, "\n")] = '\0';
    
    printf("Nuevos creditos (-1 para mantener): ");
    if (scanf("%d", &credits) != 1) {
        credits = -1;
    }
    
    if (course_list_update(courses, id, strlen(name) > 0 ? name : NULL, credits)) {
        printf("Materia modificada exitosamente.\n");
    } else {
        printf("Error al modificar materia.\n");
    }
}

void delete_course(CourseList *courses) {
    int id;
    
    printf("\n=== ELIMINAR MATERIA ===\n");
    printf("ID de la materia: ");
    if (scanf("%d", &id) != 1) {
        printf("Error: ID invalido.\n");
        return;
    }
    
    Course *course = course_list_find_by_id(courses, id);
    if (!course) {
        printf("Error: Materia no encontrada.\n");
        return;
    }
    
    printf("¿Esta seguro de eliminar %s? (s/n): ", course->name);
    clear_input_buffer();
    char confirm = getchar();
    
    if (confirm == 's' || confirm == 'S') {
        if (course_list_remove(courses, id)) {
            printf("Materia eliminada exitosamente.\n");
        } else {
            printf("Error al eliminar materia.\n");
        }
    } else {
        printf("Operacion cancelada.\n");
    }
}

void enroll_student(StudentList *students, CourseList *courses) {
    int student_id, course_id;
    
    printf("\n=== INSCRIBIR ESTUDIANTE EN MATERIA ===\n");
    printf("ID del estudiante: ");
    if (scanf("%d", &student_id) != 1) {
        printf("Error: ID invalido.\n");
        return;
    }
    
    Student *student = student_list_find_by_id(students, student_id);
    if (!student) {
        printf("Error: Estudiante no encontrado.\n");
        return;
    }
    
    printf("Estudiante: %s\n", student->name);
    printf("ID de la materia: ");
    if (scanf("%d", &course_id) != 1) {
        printf("Error: ID invalido.\n");
        return;
    }
    
    Course *course = course_list_find_by_id(courses, course_id);
    if (!course) {
        printf("Error: Materia no encontrada.\n");
        return;
    }
    
    if (student_enroll(student, course_id)) {
        printf("Estudiante inscrito en %s exitosamente.\n", course->name);
    } else {
        printf("Error: El estudiante ya esta inscrito en esta materia o alcanzo el limite.\n");
    }
}

void take_exam(StudentList *students, CourseList *courses) {
    int student_id, course_id;
    float grade;
    
    printf("\n=== RENDIR EXAMEN ===\n");
    printf("ID del estudiante: ");
    if (scanf("%d", &student_id) != 1) {
        printf("Error: ID invalido.\n");
        return;
    }
    
    Student *student = student_list_find_by_id(students, student_id);
    if (!student) {
        printf("Error: Estudiante no encontrado.\n");
        return;
    }
    
    printf("Estudiante: %s\n", student->name);
    printf("ID de la materia: ");
    if (scanf("%d", &course_id) != 1) {
        printf("Error: ID invalido.\n");
        return;
    }
    
    Course *course = course_list_find_by_id(courses, course_id);
    if (!course) {
        printf("Error: Materia no encontrada.\n");
        return;
    }
    
    Enrollment *enrollment = student_find_enrollment(student, course_id);
    if (!enrollment) {
        printf("Error: El estudiante no esta inscrito en esta materia.\n");
        return;
    }
    
    printf("Materia: %s\n", course->name);
    printf("Nota (1-10): ");
    if (scanf("%f", &grade) != 1 || grade < 1.0 || grade > 10.0) {
        printf("Error: Nota invalida.\n");
        return;
    }
    
    if (student_take_exam(student, course_id, grade)) {
        printf("Examen registrado exitosamente.\n");
        if (grade >= 4.0) {
            printf("Estado: APROBADO\n");
        } else {
            printf("Estado: DESAPROBADO\n");
        }
    } else {
        printf("Error al registrar examen.\n");
    }
}

int main() {
    StudentList *students = student_list_create();
    CourseList *courses = course_list_create();
    
    if (!students || !courses) {
        printf("Error: No se pudo inicializar el sistema.\n");
        return 1;
    }
    
    int option;
    int running = 1;
    
    printf("\n");
    printf("╔════════════════════════════════════════════════════════════╗\n");
    printf("║  Bienvenido al Sistema de Gestion de Estudiantes          ║\n");
    printf("╚════════════════════════════════════════════════════════════╝\n");
    
    while (running) {
        show_main_menu();
        
        if (scanf("%d", &option) != 1) {
            printf("Error: Opcion invalida.\n");
            clear_input_buffer();
            continue;
        }
        
        switch (option) {
            case 0:
                running = 0;
                printf("\n¡Hasta luego!\n\n");
                break;
            case 1:
                add_student(students);
                break;
            case 2:
                update_student(students);
                break;
            case 3:
                delete_student(students);
                break;
            case 4:
                student_list_display(students);
                break;
            case 5:
                search_student_by_name(students);
                break;
            case 6:
                search_student_by_age(students);
                break;
            case 7:
                view_student_detail(students, courses);
                break;
            case 8:
                add_course(courses);
                break;
            case 9:
                update_course(courses);
                break;
            case 10:
                delete_course(courses);
                break;
            case 11:
                course_list_display(courses);
                break;
            case 12:
                enroll_student(students, courses);
                break;
            case 13:
                take_exam(students, courses);
                break;
            default:
                printf("Opcion invalida. Intente nuevamente.\n");
        }
    }
    
    student_list_free(students);
    course_list_free(courses);
    
    return 0;
}
