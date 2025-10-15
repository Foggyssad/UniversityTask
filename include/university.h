#ifndef UNIVERSITY_H
#define UNIVERSITY_H

#include <stddef.h>
#include "group.h"

#define UNI_NAME_SIZE 32

typedef struct Faculty Faculty;

/**
 * @struct University
 * @brief Represets a university that owns multiple faculties.
 * 
 * @details
 * Owns dynamically allocated arrays of pointers to 'Faculty' structures.
 * Lifetime is managed by 'App'. When 'University" is destroyed,
 * all owned 'Faculty' and their owned 'Group' instances are destroyed as well.
 * 
 * 
 * @
 */
typedef struct University {
	int id;
	char name[UNI_NAME_SIZE];

	Faculty **faculties;
	size_t faculty_count, faculty_cap;
} University;

/**
 * @brief University constructor. When called the memory is allocated on the heap, instance is created.
 * 
 * @param name 
 * @return University* 
 */
University *university_create(const char *name);

/**
 * @brief University destructor. Destroys faculties and groups.
 * 
 * @param u 
 */
void university_destroy(University *u);

/**
 * @brief University name getter.
 * 
 * @param u 
 * @return const char*
 */
const char *university_get_name(const University *u);

/**
 * @brief Faculty count getter.
 * 
 * @param u 
 * @return size_t 
 */
size_t university_get_faculty_count(const University *u);

/**
 * @brief University name setter.
 * 
 * @param u 
 * @param name 
 * @return int: OK on success, ERR on error
 */
int university_set_name(University *u, const char *name);

/**
 * @brief Adds a faculty to the university and transfers ownership on success.
 * 
 * @details 
 * Links an existing 'Faculty' instance to a 'University' within an 'App'. 
 * Destruction of the 'Faculty' instance on error is managed by the funcion (callee).
 * 
 * @param u - Pointer to the 'University' instance;
 * @param f - Pointer to the 'Faculty' instance.
 * @return int: OK on success, ERR on error
 */
int university_add_faculty(University *u, struct Faculty *f);

/**
 * @brief Removes a faculty from the university and destroys it.
 * 
 * @details University's ownership with the faculty ends if this function succeeds.
 * 
 * @param f 
 * @param g 
 * @return int: OK on success, ERR on error
 */
int university_remove_faculty(University *u, struct Faculty *f);

/**
 * @brief Faculty finder across the university by id.
 * 
 * @param u 
 * @param id 
 * @return Faculty* on success, NULL on failure.
 */
Faculty *university_find_faculty(University *u, int id);

/**
 * @brief Group finder across the university by id.
 * 
 * @param u 
 * @param id 
 * @return Group* on success, NULL on failure.
 */
Group *university_find_group(University *u, int id);

/**
 * @brief Group finder across the university by name.
 * 
 * @param u 
 * @param name 
 * @return Group* on success, NULL on failure.
 */
Group *university_find_group_by_name(University *u, const char *name);

/**
 * @brief List all groups across the university.
 * 
 * @param u 
 */
void university_list_groups(University *u);

/**
 * @brief List all faculties across the university.
 * 
 * @param u 
 * @return int: OK on success, ERR on error
 */
int university_list_faculties(University *u);

/**
 * @brief Find the index of the pointer to the faculty insatnce inside the Faculty ** dynamically allocated array.
 * 
 * @param f 
 * @param u 
 * @return size_t: idx on success, SIZE 
 */
size_t find_faculty_idx_in_university(Faculty *f, University *u);

#endif