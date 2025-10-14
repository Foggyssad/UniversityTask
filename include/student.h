#ifndef STUDENT_H
#define STUDENT_H

#include <stddef.h>

#define STUDENT_NAME_SIZE 32

typedef struct Group Group;

typedef struct Student {
	int id;
	char name[STUDENT_NAME_SIZE];

	Group **groups;
	size_t group_count, group_cap;

    struct Student *prev_node, *next_node;
} Student;

typedef struct StudentList {
	Student *head, *tail;
	size_t size;
} StudentList;

void student_list_init(StudentList *s_list);
Student *student_add(StudentList *s_list, int id, const char* name);
void student_remove_node(StudentList *s_list, Student *s);
int student_remove(StudentList *s_list, int id);

const char *student_get_name(const Student *s);
int student_get_id(const Student *s);

int student_set_name(Student *s, const char *name);
int student_set_id(Student *s, int id);

int student_add_group(Student *s, Group *g);
int student_remove_group(Student *s, Group *g);

int list_students(StudentList *s_list);
int list_student_groups(Student *s);
int student_list_clear(StudentList *s_list);
Student *student_find(StudentList *s_list, int id);

#endif