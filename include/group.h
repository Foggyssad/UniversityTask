#ifndef GROUP_H
#define GROUP_H

#include <stddef.h>

#define GROUP_NAME_SIZE 32

typedef struct Student Student;

typedef struct Group {
	int id;
	char name[GROUP_NAME_SIZE];
	Student **students;
	size_t student_count, student_cap;
} Group;

Group *group_create(int id, const char *name);
void group_destroy(Group *g);
size_t find_student_idx_in_group(Student *s, Group *g);
size_t find_group_idx_in_student(const Student *s, const Group *g);

const char *group_get_name(const Group *g);
size_t group_get_student_count(const Group *g);
Student *group_get_student(const Group *g, size_t idx);

int group_set_name(Group *g, const char *name);
int group_set_id(Group *g, int id);

int group_add_student(Group *g, struct Student *s);
int group_remove_student(Group *g, struct Student *s);
int list_group_students(Group *g);

#endif