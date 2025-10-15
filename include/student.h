#ifndef STUDENT_H
#define STUDENT_H

#include <stddef.h>

#define STUDENT_NAME_SIZE 32

typedef struct Group Group;


/**
 * @struct Student
 * @brief One student node in a doubly linked list and a member of zero or more groups.
 * 
 * @details
 * Each student may belong to multiple groups across faculties, i.e. many-to-many association.
 * Lifetime is maned by the 'StudentList'. Student is referenced (not owned) by 'Group' structures.
 * 'Student' structs do not own 'Group' structs; they reference them.
 * 
 * 
 * @
 */
typedef struct Student {
	int id;
	char name[STUDENT_NAME_SIZE];

	Group **groups;
	size_t group_count, group_cap;

    struct Student *prev_node, *next_node;
} Student;

/**
 * @struct StudentList
 * @brief Conatainer for all 'Student' nodes (doubly linked list).
 * 
 * @details
 * Lifetime is managed by the 'App'. 'StudentList' owns all 'Student' nodes linked into it.
 * Conatins head, tail pointers and own size. 
 * 
 * @
 */
typedef struct StudentList {
	Student *head, *tail;
	size_t size;
} StudentList;

/**
 * @brief 
 * 
 * @param s_list 
 */
void student_list_init(StudentList *s_list);

/**
 * @brief 
 * 
 * @param s_list 
 * @param id 
 * @param name 
 * @return Student* 
 */
Student *student_add(StudentList *s_list, int id, const char* name);

/**
 * @brief 
 * 
 * @param s_list 
 * @param s 
 */
void student_remove_node(StudentList *s_list, Student *s);

/**
 * @brief 
 * 
 * @param s_list 
 * @param id 
 * @return int 
 */
int student_remove(StudentList *s_list, int id);

/**
 * @brief 
 * 
 * @param s 
 * @return const char* 
 */
const char *student_get_name(const Student *s);

/**
 * @brief 
 * 
 * @param s 
 * @return int 
 */
int student_get_id(const Student *s);

/**
 * @brief 
 * 
 * @param s 
 * @param name 
 * @return int 
 */
int student_set_name(Student *s, const char *name);

/**
 * @brief 
 * 
 * @param s 
 * @param id 
 * @return int 
 */
int student_set_id(Student *s, int id);

/**
 * @brief 
 * 
 * @param s 
 * @param g 
 * @return int 
 */
int student_add_group(Student *s, Group *g);

/**
 * @brief 
 * 
 * @param s 
 * @param g 
 * @return int 
 */
int student_remove_group(Student *s, Group *g);

/**
 * @brief 
 * 
 * @param s_list 
 * @return int 
 */
int list_students(StudentList *s_list);

/**
 * @brief 
 * 
 * @param s 
 * @return int 
 */
int list_student_groups(Student *s);

/**
 * @brief 
 * 
 * @param s_list 
 * @return int 
 */
int student_list_clear(StudentList *s_list);

/**
 * @brief 
 * 
 * @param s_list 
 * @param id 
 * @return Student* 
 */
Student *student_find(StudentList *s_list, int id);

#endif