#include "error_types.h"
#include "university.h"
#include "faculty.h"
#include "group.h"
#include "student.h"
#include "utils.h"

#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <stdio.h>

size_t find_group_idx_in_faculty(Group *g, Faculty *f)
{
	if (g == NULL || f == NULL || f->group_count == 0 || f->groups == NULL)
		return SIZE_MAX;
		
	for (size_t i = 0; i < f->group_count; i++) {
		if (f->groups[i] == g) {
			return i;
		}
	}
	return SIZE_MAX;
}

Faculty *faculty_create(int id, const char *name)
{
	Faculty *f = (Faculty *)malloc(sizeof(Faculty));
	if (f == NULL)
		return NULL;
	
	faculty_set_id(f, id);
	faculty_set_name(f, name);
	f->groups = NULL;
	f->group_count = 0;
	f->group_cap = 0;

	return f;
}

void faculty_destroy(Faculty *f)
{
	for (size_t i = 0; i < f->group_count; i++)
         if (f->groups[i] != NULL) group_destroy(f->groups[i]);

    free(f->groups);
	free(f);
}

const char *faculty_get_name(const Faculty *f) { return f->name; }

int faculty_set_id(Faculty *f, int id)
{
	f->id = id;
	return OK;
}

int faculty_set_name(Faculty *f, const char *name)
{
	if (f == NULL || name == NULL)
	    return ERR;
	strncpy(f->name, name, sizeof(f->name) - 1);
	f->name[sizeof(f->name) - 1] = '\0';
    return OK;
}

int faculty_add_group(University *u, Faculty *f, struct Group *g)
{
	if (g == NULL)
		return ERR;

	if (u == NULL || f == NULL)
	{
		group_destroy(g);
		return ERR;
	}
	
	if (faculty_find_group(f, g->id) != NULL)
	{
		if (faculty_find_group(f, g->id) == g)
			return ERR;

		group_destroy(g);
		return ERR;
	}
	if (university_find_group(u, g->id) != NULL)
	{
		group_destroy(g);
		return ERR;
	}
	
	size_t next = f->group_count + 1;
    size_t element_size = sizeof *f->groups;

    void *tmp_ptr = reserve_ptr_arr(f->groups, element_size,
		            &f->group_cap, next);
	
    if (tmp_ptr == NULL)
	{
		group_destroy(g);
		return ERR;
	}

    f->groups = (Group **)tmp_ptr;
	f->groups[f->group_count++] = g;
	return OK;
}

int faculty_remove_group(Faculty *f, Group *g)
{
	if (g == NULL || f == NULL)
		return ERR;

	size_t idx = find_group_idx_in_faculty(g, f);
	if (idx == SIZE_MAX)
		return ERR;

		
	size_t last = --f->group_count;
	f->groups[idx] = f->groups[last];
	f->groups[last] = NULL;

	group_destroy(g);

	return OK;
}

Group *faculty_find_group(Faculty *f, int id)
{
	if (f == NULL)
		return NULL;

	for (size_t i = 0; i < f->group_count; i++)
	{
		Group *g = f->groups[i];
		if (g != NULL && g->id == id)
			return g;
	}
	return NULL;
}

int faculty_list_groups(Faculty *f)
{
	if (f == NULL)
		return ERR;
	
	for(size_t i = 0; i < f->group_count; i++) 
		printf("%d %s\n", f->groups[i]->id, f->groups[i]->name);
	

	return OK;
}

