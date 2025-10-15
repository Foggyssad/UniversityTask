#ifndef FACULTY_H
#define FACULTY_H

#include <stdint.h>
#include <stddef.h>

#define FACULTY_NAME_SIZE 32

typedef struct University University;

typedef struct Group Group;

/**
 * @struct Faculty
 * @brief Represets a faculty that contains multiple groups within a university.
 * 
 * @details
 * Owns dynamically allocated arrays of pointers to 'Group' structures.
 * Lifetime is managed by 'University'. When 'University" is destroyed,
 * all owned 'Faculty' and their owned 'Group' instances are destroyed as well.
 * 
 * @
 */
typedef struct Faculty {
	int id;
	char name[FACULTY_NAME_SIZE];

	Group **groups;
	size_t group_count, group_cap;
} Faculty;

/**
 * @brief Faculty constructor. When called, the instance of the faculty is created.
 * 
 * @param id 
 * @param name 
 * @return Faculty* on success, NULL on failure.
 */
Faculty *faculty_create(int id, const char *name);

/**
 * @brief Faculty destructor. When called, the heap allocated mamery is freed and the instance is destroyed.
 * 		  All groups owned by the pointed 'Faculty' instance are destroyed. 
 * 
 * @param f 
 */
void faculty_destroy(Faculty *f);

/**
 * @brief Faculty name getter.
 * 
 * @param f 
 * @return const char* on success, NULL on failure.
 */
const char *faculty_get_name(const Faculty *f);

/**
 * @brief Faculty group count getter.
 * 
 * @param f 
 * @return size_t: idx on success, SIZE_MAX on failure.
 */
size_t faculty_get_group_count(const Faculty *f);

/**
 * @brief Faculty name setter.
 * 
 * @param f
 * @param name 
 * @return int: OK on success, ERR on error
 */
int faculty_set_name(Faculty *f, const char *name);

/**
 * @brief Faculty id setter.
 * 
 * @param f 
 * @param id 
 * @return int: OK on success, ERR on error
 */
int faculty_set_id(Faculty *f, int id);

/**
 * @brief Adds a group to a faculty and transfers ownership on success.
 * 
 * @details 
 * Links an existing 'Group' instance to a 'Faculty' within a 'University'. 
 * Destruction of the 'Group' instance on error is managed by the funcion (callee).
 * 
 * @param u - Pointer to the 'University' instance;
 * @param f - Pointer to the 'Faculty' instance;
 * @param g - Pointer to the 'Group' instance.
 * @return int: OK on success, ERR on error
 */
int faculty_add_group(University *u, Faculty *f, Group *g);

/**
 * @brief Removes a group from a faculty and destroys it.
 * 
 * @details Faculty's ownership with the group end if this function succeeds.
 * 
 * @param f 
 * @param g 
 * @return int: OK on success, ERR on error
 */
int faculty_remove_group(Faculty *f, Group *g);

/**
 * @brief Find the index of the pointer to the 'Group' instance inside the Faculty's (Group **) container.
 * 
 * @param g 
 * @param f 
 * @return int: OK on success, ERR on error
 */
size_t find_group_idx_in_faculty(Group *g, Faculty *f);

/**
 * @brief Group finder inside the faculty by id.
 * 
 * @param f 
 * @param id 
 * @return Group* on success, NULL on error
 */
Group *faculty_find_group(Faculty *f, int id);

/**
 * @brief List all groups that belong to a particular faculty.
 * 
 * @param f 
 * @return int: OK on success, ERR on error
 */
int faculty_list_groups(Faculty *f);

#endif