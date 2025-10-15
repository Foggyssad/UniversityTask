#include "error_types.h"
#include "university.h"
#include "group.h"
#include "faculty.h"
#include "utils.h"

#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

University *university_create(const char *name)
{
	University *u = (University *)malloc(sizeof(University));
	if (u == NULL)
		return NULL;

	university_set_name(u, name);
	u->faculties = NULL;
	u->faculty_count = 0;
	u->faculty_cap = 0;

	return u;
}

void university_destroy(University *u)
{
	if (u == NULL)
		return;

	for (size_t i = 0; i < u->faculty_count; i++)
         if (u->faculties[i] != NULL) 
		 	faculty_destroy(u->faculties[i]);
    
    free(u->faculties);
	free(u);
}

const char *university_get_name(const University *u) { return u->name; }

int university_set_name(University *u, const char *name)
{
	if (u == NULL || name == NULL)
		return -1;
	strncpy(u->name, name, sizeof(u->name) - 1);
	u->name[sizeof(u->name) - 1] = '\0';
    return OK;
}

int university_add_faculty(University *u, struct Faculty *f)
{
	if (f == NULL)
		return ERR;

	if (u == NULL)
	{
		faculty_destroy(f);
		return ERR;
	}
	
	if (find_faculty_idx_in_university(f, u) != SIZE_MAX)
	{
		faculty_destroy(f);
		return ERR;
	}
	
	size_t next = u->faculty_count + 1;
    size_t element_size = sizeof *u->faculties;

    void *tmp_ptr = reserve_ptr_arr(u->faculties, element_size,
		                            &u->faculty_cap, next);
    
    if (tmp_ptr == NULL)
	{
		faculty_destroy(f);
		return ERR;
	}

    u->faculties = (Faculty **)tmp_ptr;
	u->faculties[u->faculty_count++] = f;
	return OK;
}

size_t find_faculty_idx_in_university(Faculty *f, University *u)
{
	if (u == NULL || f == NULL || u->faculty_count == 0 || u->faculties == NULL)
		return SIZE_MAX;
		
	for (size_t i = 0; i < u->faculty_count; i++) {
		if (u->faculties[i]->id == f->id) {
			return i;
		}
	}
	return SIZE_MAX;
}

int university_remove_faculty(University *u, struct Faculty *f)
{
	if (u == NULL || f == NULL)
		return ERR;

	size_t idx = find_faculty_idx_in_university(f, u);
	if (idx == SIZE_MAX)
		return ERR;

	size_t last = --u->faculty_count;
	u->faculties[idx] = u->faculties[last];
	u->faculties[last] = NULL;

	faculty_destroy(f);

	return OK;
}

Faculty *university_find_faculty(University *u, int id)
{
	for (size_t i = 0; i < u->faculty_count; i++)
	{
		Faculty *f = u->faculties[i];
		if (f != NULL && f->id == id)
			return f;
	}
	return NULL;
}

Group *university_find_group(University *u, int id)
{
	if (u == NULL)
		return NULL;
	
	for (size_t i = 0; i < u->faculty_count; i++)
		for(size_t j = 0; j < u->faculties[i]->group_count; j++) 
			if (u->faculties[i]->groups[j]->id == id)
				return u->faculties[i]->groups[j];
	return NULL;
}

Group *university_find_group_by_name(University *u, const char *name)
{
	for (size_t i = 0; i < u->faculty_count; i++)
		for(size_t j = 0; j < u->faculties[i]->group_count; j++) 
			if (strcmp(u->faculties[i]->groups[j]->name, name) == OK)
				return u->faculties[i]->groups[j];
	return NULL;
}

void university_list_groups(University *u)
{
	for (size_t i = 0; i < u->faculty_count; i++)
		for(size_t j = 0; j < u->faculties[i]->group_count; j++) 
			printf("%d %s\n", u->faculties[i]->groups[j]->id, u->faculties[i]->groups[j]->name);
}

int university_list_faculties(University *u)
{
	if (u == NULL)
		return ERR;
	
	for (size_t i = 0; i < u->faculty_count; i++)
		printf("%d %s\n", u->faculties[i]->id, u->faculties[i]->name);
	
	return OK;
}