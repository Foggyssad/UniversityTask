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
 * @brief Initialization of the fields of the 'StudentList'
 * 
 * @param s_list 
 */
void student_list_init(StudentList *s_list);

/**
 * @brief Create an instance of the 'Student' and add it into the 'StudentList' linked list.
 * 
 * @param s_list 
 * @param id 
 * @param name 
 * @return Student* on success, NULL on failure.
 */
Student *student_add(StudentList *s_list, int id, const char* name);

/**
 * @brief remove a particular 'Student' node from the 'StudentList' linked list.
 * 
 * @param s_list 
 * @param s 
 */
void student_remove_node(StudentList *s_list, Student *s);

/**
 * @brief Find a particular student by id and call student_remove_node().
 * 
 * @param s_list 
 * @param id 
 * @return int: OK on success, ERR on failure. 
 */
int student_remove(StudentList *s_list, int id);

/**
 * @brief Student name getter.
 * 
 * @param s 
 * @return const char* on success, NULL on failure.
 */
const char *student_get_name(const Student *s);

/**
 * @brief Student id getter.
 * 
 * @param s 
 * @return int: OK on success, ERR on failure.
 */
int student_get_id(const Student *s);

/**
 * @brief Student name setter.
 * 
 * @param s 
 * @param name 
 * @return int: OK on success, ERR on failure.
 */
int student_set_name(Student *s, const char *name);

/**
 * @brief Student id setter.
 * 
 * @param s 
 * @param id 
 * @return int: OK on success, ERR on failure.
 */
int student_set_id(Student *s, int id);

/**
 * @brief Enroll a particular student into a group.
 * 
 * @param s 
 * @param g 
 * @return int: OK on success, ERR on failure.
 */
int student_add_group(Student *s, Group *g);

/**
 * @brief Unenroll a particualr student from the group.
 * 
 * @param s 
 * @param g 
 * @return int: OK on success, ERR on failure.
 */
int student_remove_group(Student *s, Group *g);

/**
 * @brief List all students across the university.
 * 
 * @param s_list 
 * @return int: OK on success, ERR on failure.
 */
int list_students(StudentList *s_list);

/**
 * @brief List all groups that a particular student is enrolled into.
 * 
 * @param s 
 * @return int: OK on success, ERR on failure.
 */
int list_student_groups(Student *s);

/**
 * @brief Destroy every student node in the StudentList linked list and call student_list_init().
 * 
 * @param s_list 
 * @return int: OK on success, ERR on failure.
 */
int student_list_clear(StudentList *s_list);

/**
 * @brief Traverse the linked list and find 
 * 
 * @param s_list 
 * @param id 
 * @return Student* on success, NULL on failure.
 */
Student *student_find(StudentList *s_list, int id);

#endif