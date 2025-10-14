#ifndef FACULTY_H
#define FACULTY_H

#include <stdint.h>
#include <stddef.h>

#define FACULTY_NAME_SIZE 32

typedef struct University University;

typedef struct Group Group;

typedef struct Faculty {
	int id;
	char name[FACULTY_NAME_SIZE];

	Group **groups;
	size_t group_count, group_cap;
} Faculty;

Faculty *faculty_create(int id, const char *name);
void faculty_destroy(Faculty *f);

const char *faculty_get_name(const Faculty *f);
size_t faculty_get_group_count(const Faculty *f);
Group *faculty_get_group(const Faculty *f, size_t idx);

int faculty_set_name(Faculty *f, const char *name);
int faculty_set_id(Faculty *f, int id);

int faculty_add_group(University *u, Faculty *f, Group *g);
int faculty_remove_group(Faculty *f, Group *g);

size_t find_group_idx_in_faculty(Group *g, Faculty *f);
Group *faculty_find_group(Faculty *f, int id);
int faculty_list_groups(Faculty *f);

#endif