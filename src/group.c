
#include "error_types.h"
#include "student.h"
#include "group.h"
#include "utils.h"

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

size_t find_student_idx_in_group(Student *s, Group *g)
{
	if (s == NULL || g == NULL || g->student_count == 0 || g->students == NULL)
		return SIZE_MAX;
		
	for (size_t i = 0; i < g->student_count; i++) 
	{
		if (g->students[i] == s) 
		{
			return i;
		}
	}

	return SIZE_MAX;
}

size_t find_group_idx_in_student(const Student *s, const Group *g)
{
	if (s == NULL || g == NULL || s->group_count == 0 || s->groups == NULL)
		return SIZE_MAX;
	
	for (size_t i = 0; i < s->group_count; i++) 
	{
		if (s->groups[i] == g) 
		{
			return i;
		}
	}

	return SIZE_MAX;
}

Group *group_create(int id, const char *name)
{
	Group *g = (Group *)malloc(sizeof(Group));
	if (g == NULL)
		return NULL;

	group_set_id(g, id);
	group_set_name(g, name);
	g->students = NULL;
	g->student_count = 0;
	g->student_cap = 0;

	return g;
}

void group_destroy(Group *g)
{
	if (g == NULL)
		return;
	
	while(g->student_count > 0)
	{
		Student *s = g->students[g->student_count - 1];
		group_remove_student(g, s);
	}

	free(g->students);
	free(g);
}

const char *group_get_name(const Group *g) { return g->name; }

int group_set_id(Group *g, int id)
{
	if (g == NULL)
		return ERR;
	g->id = id;
	return OK;
}

int group_set_name(Group *g, const char *name)
{
	if (g == NULL || name == NULL)
	    return ERR;
	strncpy(g->name, name, sizeof(g->name) - 1);
	g->name[sizeof(g->name) - 1] = '\0';
    return OK;
}

int group_add_student(Group *g, struct Student *s)
{
	if (g == NULL || s == NULL)
		return ERR;
	
	if (find_student_idx_in_group(s, g) != SIZE_MAX)
		return OK;
	
	size_t next = g->student_count + 1;
    size_t element_size = sizeof *g->students;

    void *tmp_g_ptr = reserve_ptr_arr(g->students, element_size,
		                			  &g->student_cap, next);
    
    if (tmp_g_ptr == NULL) return ERR;

	void *tmp_s_ptr = reserve_ptr_arr(s->groups, element_size,
		            				  &s->group_cap, next);
	
	if (tmp_s_ptr == NULL)
	    return ERR;

	g->students = (Student **)tmp_g_ptr;
	g->students[g->student_count++] = s;
	
	s->groups = (Group **)tmp_s_ptr;
	s->groups[s->group_count++] = g;

	return OK;
}

int group_remove_student(Group *g, Student *s)
{
	if (g == NULL || s == NULL)
		return ERR;
	
	size_t s_idx = find_student_idx_in_group(s, g);
	if (s_idx == SIZE_MAX)
		return ERR;
	
	size_t last_s = g->student_count - 1;
	g->students[s_idx] = g->students[last_s];
	g->students[last_s] = NULL;
	g->student_count = last_s;

	size_t g_idx = find_group_idx_in_student(s, g);
	if (g_idx == SIZE_MAX)
		return ERR;

	size_t last_g = s->group_count - 1;
	s->groups[g_idx] = s->groups[last_g];
	s->groups[last_g] = NULL;
	s->group_count = last_g;

	return OK;
}

void list_groups(StudentList *s_list)
{
	Student *s = s_list->head;

	while(s != NULL)
	{
		printf("%d %s\n", s->id, s->name);
		s = s->next_node;
	}
}

int list_group_students(Group *g)
{
	if (g == NULL)
		return ERR;
	
	for (size_t i = 0; i < g->student_count; i++)
	{
		Student *s = g->students[i];
		if (s) printf("%d %s\n", s->id, s->name);
	}
	return OK;
}