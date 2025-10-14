#include "app.h"

void app_init(App *a, const char *uni_name)
{
    a->uni = university_create(uni_name);
    student_list_init(&a->student_list);
}

void app_destroy(App *a)
{
    student_list_clear(&a->student_list);
    
    if (a->uni != NULL)
    {
        university_destroy(a->uni);
        a->uni = NULL;
    }
}