#include "error_types.h"
#include "student.h"
#include "group.h"
#include "utils.h"

#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

void student_list_init(StudentList *s_list)
{
	s_list->head = s_list->tail = 0;
	s_list->size = 0;
}

Student *student_add(StudentList *s_list, int id, const char *name)
{
	if (s_list == NULL)
		return NULL;

	if (student_find(s_list, id) != NULL)
		return NULL;

	Student *s = (Student *)calloc(1, sizeof(Student));
	if (s == NULL)
		return NULL;
	
	student_set_id(s, id);
	student_set_name(s, name);
	s->prev_node = s_list->tail;
	s->next_node = NULL;

	if(s_list->tail != NULL)
	   s_list->tail->next_node = s;
	else
	   s_list->head = s;
	
	s_list->tail = s;

	s_list->size++;

	return s;
}

void student_remove_node(StudentList *s_list, Student *s)
{
	if (s_list == NULL || s == NULL)
		return;
	
	if(s->prev_node != NULL)
	   s->prev_node->next_node = s->next_node;
	else
	   s_list->head = s->next_node;

	if(s->next_node != NULL)
	   s->next_node->prev_node = s->prev_node;
	else
	   s_list->tail = s->prev_node;
	
	free(s->groups);
	free(s);

	s_list->size--;
}

Student *student_find(StudentList *s_list, int id)
{
	if (s_list == NULL)
		return NULL;
	Student *s = s_list->head;
	
	while(s != NULL)
	{
		if (student_get_id(s) == id)
			return s;
		s = s->next_node;
	}
	return NULL;
}

int student_remove(StudentList *s_list, int id)
{
	Student *s = student_find(s_list, id);
	if (s == NULL)
		return ERR;
	
	while(s->group_count > 0)
	{
		Group *g = s->groups[s->group_count - 1];
		group_remove_student(g, s);
	}

	student_remove_node(s_list, s);
	
	return OK;
}

const char *student_get_name(const Student *s) { return s->name; }

int student_get_id(const Student *s) { return s->id; }

int student_set_name(Student *s, const char *name)
{
	if (s == NULL || name == NULL)
	    return ERR;
	
	
	strncpy(s->name, name, sizeof(s->name) - 1);
	s->name[sizeof(s->name) - 1] = '\0';
    return OK;
}

int student_set_id(Student *s, int id)
{
	if (s == NULL)
		return ERR;
	s->id = id;
	return OK;
}

int student_add_group(Student *s, Group *g)
{
	if (s == NULL || g == NULL)
		return ERR;
	
	return group_add_student(g, s);
}

int student_remove_group(Student *s, Group *g)
{
	if (s == NULL || g == NULL)
		return ERR;
	
	return group_remove_student(g, s);
}

int list_students(StudentList *s_list)
{
	if (s_list == NULL)
		return ERR;
	
	Student *s = s_list->head;

	while(s != NULL)
	{
		printf("%d %s\n", s->id, s->name);
		s = s->next_node;
	}
	return OK;
}

int list_student_groups(Student *s)
{
	if (s == NULL)
		return ERR;
	
	for (size_t i = 0; i < s->group_count; i++)
	{
		Group *g = s->groups[i];
		if (g) printf("%d %s\n", g->id, g->name);
	}
	return OK;
}

int student_list_clear(StudentList *s_list)
{
	if (s_list == NULL)
		return ERR;
	
	Student *s = s_list->head;

	while(s != NULL)
	{
		Student *next_one = s->next_node;

		while (s->group_count > 0)
		{
			Group *g = s->groups[0];
			student_remove_group(s, g);
		}

		free(s->groups);
		free(s);
		s = next_one;
	}
	student_list_init(s_list);

	return OK;
}