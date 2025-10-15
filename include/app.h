#ifndef APP_H
#define APP_H

#include "student.h"
#include "university.h"

/**
 * @struct App
 * @brief Top-level application container. 
 * 
 * The 'App' structure encapsulates one 'University' instance and a global 'StudentList' used for student tracking.
 * 
 * Lifetime and Ownership:
 * - 'App' owns the 'University*' instance and the 'StudentList'.
 * - The 'University' owns all 'Faculty' objects 
 * - Each 'Faculty' owns its 'Group' objects; 
 * - There cannot be two 'Group' instances with the same ID across the university.
 * - Each 'Group' maintains non-owning references to 'Student' objects.
 * 
 * Cleanup:
 * Call app_destroy() to free the data recursively:
 * 
 * App -> University -> Faculties -> Groups.
 *    ↘ 
 *     StudentList -> Students
 * 
 */
typedef struct App {
    University *uni;
    StudentList student_list;
} App;

/**
 * @brief 
 * 
 * @param a 
 * @param uni_name 
 */
void app_init(App *a, const char *uni_name);

/**
 * @brief 
 * 
 * @param a 
 */
void app_destroy(App *a);

#endif