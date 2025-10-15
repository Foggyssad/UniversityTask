#ifndef GROUP_H
#define GROUP_H

#include <stddef.h>

#define GROUP_NAME_SIZE 32

typedef struct Student Student;

/**
 * @struct Group
 * @brief Represets a faculty that contains multiple groups within a university.
 * 
 * @details
 * Lifetime is managed by the 'Faculty', i.e. ownership.
 * 'Group' structures are detroyed when their owning 'Faculty' is destroyed.
 * 'Group' structs do not free students; they maintain a dynamic array of pointers to 'Student' instances (Student **), they reference them.
 * 
 * @
 */
typedef struct Group {
	int id;
	char name[GROUP_NAME_SIZE];
	Student **students;
	size_t student_count, student_cap;
} Group;

/**
 * @brief Group Constructor. When called allocated memory, creates instance.
 * 
 * @param id 
 * @param name 
 * @return Group* on success, NULL on failure.
 */
Group *group_create(int id, const char *name);

/**
 * @brief Destructor of the 'Group' instance.
 * 
 * @param g 
 */
void group_destroy(Group *g);

/**
 * @brief Find the index of the pointer to the 'Student' instance inside the Group's (Student **) container.
 * 
 * @param s 
 * @param g 
 * @return size_t: idx on success, SIZE_MAX on failure.
 */
size_t find_student_idx_in_group(Student *s, Group *g);

/**
 * @brief Find the index of the pointer to the 'Group' instance inside the Student's (Group **) container.
 * 
 * @param s 
 * @param g 
 * @return size_t: idx on success, SIZE_MAX on failure.
 */
size_t find_group_idx_in_student(const Student *s, const Group *g);

/**
 * @brief Group name getter.
 * 
 * @param g 
 * @return const char* on success, NULL on failure.
 */
const char *group_get_name(const Group *g);

/**
 * @brief Student count getter.
 * 
 * @param g 
 * @return size_t: student_count on success, (size_t)ERR on failure.
 */
size_t group_get_student_count(const Group *g);

/**
 * @brief 
 * 
 * @param g 
 * @param idx 
 * @return Student* on success, NULL on failure.
 */
Student *group_get_student(const Group *g, size_t idx);

/**
 * @brief 
 * 
 * @param g 
 * @param name 
 * @return int 
 */
int group_set_name(Group *g, const char *name);

/**
 * @brief 
 * 
 * @param g 
 * @param id 
 * @return int 
 */
int group_set_id(Group *g, int id);

/**
 * @brief 
 * 
 * @param g 
 * @param s 
 * @return int 
 */
int group_add_student(Group *g, struct Student *s);

/**
 * @brief 
 * 
 * @param g 
 * @param s 
 * @return int 
 */
int group_remove_student(Group *g, struct Student *s);

/**
 * @brief 
 * 
 * @param g 
 * @return int 
 */
int list_group_students(Group *g);

#endif