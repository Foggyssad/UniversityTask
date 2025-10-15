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
 * 
 * 
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
 * @brief 
 * 
 * @param name 
 * @return University* 
 */
University *university_create(const char *name);

/**
 * @brief 
 * 
 * @param u 
 */
void university_destroy(University *u);

/**
 * @brief 
 * 
 * @param u 
 * @return const char* 
 */
const char *university_get_name(const University *u);

/**
 * @brief 
 * 
 * @param u 
 * @return size_t 
 */
size_t university_get_faculty_count(const University *u);

/**
 * @brief 
 * 
 * @param u 
 * @param idx 
 * @return Faculty* 
 */
Faculty *university_get_faculty(const University *u, size_t idx);

/**
 * @brief 
 * 
 * @param u 
 * @param name 
 * @return int 
 */
int university_set_name(University *u, const char *name);

/**
 * @brief 
 * 
 * @param u 
 * @param f 
 * @return int 
 */
int university_add_faculty(University *u, struct Faculty *f);

/**
 * @brief 
 * 
 * @param u 
 * @param f 
 * @return int 
 */
int university_remove_faculty(University *u, struct Faculty *f);

/**
 * @brief 
 * 
 * @param u 
 * @param id 
 * @return Faculty* 
 */
Faculty *university_find_faculty(University *u, int id);

/**
 * @brief 
 * 
 * @param u 
 * @param id 
 * @return Group* 
 */
Group *university_find_group(University *u, int id);

/**
 * @brief 
 * 
 * @param u 
 * @param name 
 * @return Group* 
 */
Group *university_find_group_by_name(University *u, const char *name);

/**
 * @brief 
 * 
 * @param u 
 */
void university_list_groups(University *u);

/**
 * @brief 
 * 
 * @param u 
 * @return int 
 */
int university_list_faculties(University *u);

/**
 * @brief 
 * 
 * @param f 
 * @param u 
 * @return size_t 
 */
size_t find_faculty_idx_in_university(Faculty *f, University *u);

#endif