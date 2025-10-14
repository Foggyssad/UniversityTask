#ifndef APP_H
#define APP_H

#include "student.h"
#include "university.h"

typedef struct App {
    University *uni;
    StudentList student_list;
} App;

void app_init(App *a, const char *uni_name);
void app_destroy(App *a);

#endif