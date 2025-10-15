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
 * @brief 
 * 
 * @param id 
 * @param name 
 * @return Faculty* 
 */
Faculty *faculty_create(int id, const char *name);

/**
 * @brief 
 * 
 * @param f 
 */
void faculty_destroy(Faculty *f);

/**
 * @brief 
 * 
 * @param f 
 * @return const char* 
 */
const char *faculty_get_name(const Faculty *f);

/**
 * @brief 
 * 
 * @param f 
 * @return size_t 
 */
size_t faculty_get_group_count(const Faculty *f);

/**
 * @brief 
 * 
 * @param f 
 * @param idx 
 * @return Group* on success, NULL on error
 */
Group *faculty_get_group(const Faculty *f, size_t idx);

/**
 * @brief 
 * 
 * @param f 
 * @param name 
 * @return int: OK on success, ERR on error
 */
int faculty_set_name(Faculty *f, const char *name);

/**
 * @brief 
 * 
 * @param f 
 * @param id 
 * @return int: OK on success, ERR on error
 */
int faculty_set_id(Faculty *f, int id);

/**
 * @brief 
 * 
 * @param u 
 * @param f 
 * @param g 
 * @return int: OK on success, ERR on error
 */
int faculty_add_group(University *u, Faculty *f, Group *g);

/**
 * @brief 
 * 
 * @param f 
 * @param g 
 * @return int: OK on success, ERR on error
 */
int faculty_remove_group(Faculty *f, Group *g);

/**
 * @brief 
 * 
 * @param g 
 * @param f 
 * @return int: OK on success, ERR on error
 */
size_t find_group_idx_in_faculty(Group *g, Faculty *f);

/**
 * @brief 
 * 
 * @param f 
 * @param id 
 * @return Group* on success, NULL on error
 */
Group *faculty_find_group(Faculty *f, int id);

/**
 * @brief 
 * 
 * @param f 
 * @return int: OK on success, ERR on error
 */
int faculty_list_groups(Faculty *f);

#endif