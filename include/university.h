#ifndef UNIVERSITY_H
#define UNIVERSITY_H

#include <stddef.h>
#include "group.h"

#define UNI_NAME_SIZE 32

typedef struct Faculty Faculty;

typedef struct University {
	int id;
	char name[UNI_NAME_SIZE];

	Faculty **faculties;
	size_t faculty_count, faculty_cap;
} University;

University *university_create(const char *name);
void university_destroy(University *u);

const char *university_get_name(const University *u);
size_t university_get_faculty_count(const University *u);
Faculty *university_get_faculty(const University *u, size_t idx);

int university_set_name(University *u, const char *name);

int university_add_faculty(University *u, struct Faculty *f);
int university_remove_faculty(University *u, struct Faculty *f);

Faculty *university_find_faculty(University *u, int id);
Group *university_find_group(University *u, int id);
Group *university_find_group_by_name(University *u, const char *name);

void university_list_groups(University *u);
int university_list_faculties(University *u);
size_t find_faculty_idx_in_university(Faculty *f, University *u);

#endif