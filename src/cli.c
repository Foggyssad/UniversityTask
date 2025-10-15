#define _POSIX_C_SOURCE 200809L

#include "error_types.h"
#include "app.h"
#include "cli.h"
#include "student.h"
#include "faculty.h"
#include "group.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

typedef int (*cmd_fn_ptr)(App *a, int argc, char **argv);

typedef struct Command {
    const char *name;
    cmd_fn_ptr fn;
    const char * help_field;
} Command;

static int tokenizer(char *line, char **argv, int maxv)
{
    int argc = 0;
    char *save = NULL;

    char *token = strtok_r(line, " \t\r\n", &save);
    while (token != NULL && argc < maxv)
    {
        argv[argc++] = token;
        token = strtok_r(NULL, " \t\r\n", &save);
    }
    return argc;
}

static int cmd_add_faculty(App *a, int argc, char **argv)
{
    
    if (university_find_faculty(a->uni, atoi(argv[0])) != NULL)
        return ERR;

    if (argc < 2)
        return ERR;
    else
        if (argc >= 3)
        {
            char name[128] = "";

            for (int i = 1; i < argc; i++)
            {
                if (i > 1)
                    strcat(name, " ");
                    
                strcat(name, argv[i]);
            }

            int id = atoi(argv[0]);
            Faculty *f = faculty_create(id, name);
            return university_add_faculty(a->uni, f);
        }
    int id = atoi(argv[0]);
    
    Faculty *f = faculty_create(id, argv[1]);
    return university_add_faculty(a->uni, f);
}

static int cmd_remove_faculty(App *a, int argc, char **argv)
{
    if (argc < 1)
        return ERR;

    int id = atoi(argv[0]);
    Faculty *f = university_find_faculty(a->uni, id);
    return university_remove_faculty(a->uni, f);
}

static int cmd_list_faculties(App *a, int argc, char **argv)
{
    (void)argc;
    (void)argv;
    university_list_faculties(a->uni);
    return OK;
}

static int cmd_add_student(App *a, int argc, char **argv)
{
    if (argc < 2)
        return ERR;

    int id = atoi(argv[0]);
    char *name = argv[1];
    Student *s = student_add(&a->student_list, id, name);
    return (s != NULL) ? OK : ERR;
}

static int cmd_remove_student(App *a, int argc, char **argv)
{
    if (argc < 1)
        return ERR;
    
    int id = atoi(argv[0]);
    return student_remove(&a->student_list, id);
}

static int cmd_list_students(App *a, int argc, char **argv)
{
    (void)argc;
    (void)argv;
    list_students(&a->student_list);
    return OK;
}

static int cmd_list_groups(App *a, int argc, char **argv)
{
    (void)argc;
    (void)argv;
    university_list_groups(a->uni);
    return OK;
}

static int cmd_student_list_groups(App *a, int argc, char **argv)
{
    if (argc < 1)
        return ERR;
    
    int id = atoi(argv[0]);
    Student *s = student_find(&a->student_list, id);
    return list_student_groups(s);
}

static int cmd_add_group(App *a, int argc, char **argv)
{
    if (argc < 3)
        return ERR;
    
    int faculty_id = atoi(argv[0]);
    int group_id = atoi(argv[1]);

    if (university_find_faculty(a->uni, faculty_id) == NULL || university_find_group(a->uni, group_id) != NULL)
        return ERR;
    
    
    char group_name[128] = "";
    strcpy(group_name, argv[2]);

    if (argc > 3)
    {
        for (int i = 3; i < argc; i++)
            {
                strcat(group_name, " ");
                strcat(group_name, argv[i]);
            }
    }

    Faculty *f = university_find_faculty(a->uni, faculty_id);
    Group *g = group_create(group_id, group_name);
    return faculty_add_group(a->uni, f, g);
}

static int cmd_remove_group(App *a, int argc, char **argv)
{
    if (argc < 2)
        return ERR;
    
    int faculty_id = atoi(argv[0]);
    int group_id = atoi(argv[1]);
    Faculty *f = university_find_faculty(a->uni, faculty_id);
    Group *g = faculty_find_group(f, group_id);
    return faculty_remove_group(f, g);
}

static int cmd_faculty_list_groups(App *a, int argc, char **argv)
{
    if (argc < 1)
        return ERR;
    
    int id = atoi(argv[0]);
    Faculty *f = university_find_faculty(a->uni, id);
    return faculty_list_groups(f);
}

static int cmd_group_list_students(App *a, int argc, char **argv)
{
    if (argc < 1)
        return ERR;

    int id = atoi(argv[0]);
    Group *g = university_find_group(a->uni, id);
    return list_group_students(g);
}

static int cmd_enroll(App *a, int argc, char **argv)
{
    if (argc < 2)
        return ERR;
    int student_id = atoi(argv[0]);
    Student *s = student_find(&a->student_list, student_id);
    int group_id = atoi(argv[1]);
    Group *g = university_find_group(a->uni, group_id);
    return group_add_student(g, s);
}

static int cmd_unenroll(App *a, int argc, char **argv)
{
    if (argc < 2)
        return ERR;
    
    int student_id = atoi(argv[0]);
    Student *s = student_find(&a->student_list, student_id);
    int group_id = atoi(argv[1]);
    Group *g = university_find_group(a->uni, group_id);
    return group_remove_student(g, s);
}

static int cmd_uni_info(App *a, int argc, char **argv)
{
    (void)argc;
    (void)argv;
    University *u = a->uni;

    if (u == NULL)
        return ERR;

    size_t group_total_count = 0;
    for (size_t i = 0; i < u->faculty_count; i++)
        if (u->faculties[i])
            group_total_count += u->faculties[i]->group_count;
    
    printf("University: %s\n", u->name);
    printf("Faculties: %zu\n", u->faculty_count);
    printf("Groups: %zu\n", group_total_count);
    printf("Students: %zu\n", a->student_list.size);
    return OK;
}

static int cmd_uni_rename(App *a, int argc, char **argv)
{
    if (argc < 2)
        return university_set_name(a->uni, argv[0]);
    else
    {
        char name[128] = "";

            for (int i = 0; i < argc; i++)
            {
                if (i > 0)
                    strcat(name, " ");
                    
                strcat(name, argv[i]);
            }
        return university_set_name(a->uni, name);
    }
    return ERR;
}

static int cmd_quit(App *a, int argc, char **argv)
{
    (void)a;
    (void)argc;
    (void)argv;
    return QUIT;
}

static int cmd_help(App *a, int argc, char **argv);

static const Command commands[] = {
    {"list-groups", cmd_list_groups, "list-groups - list groups across the whole university in such format: <id> <name>"},
    {"add-faculty", cmd_add_faculty, "add-faculty <id> <name> - add faculty which is in composition relationship with the university"},
    {"remove-faculty", cmd_remove_faculty, "remove-faculty <id> - remove faculty from the university"},
    {"list-faculties", cmd_list_faculties, "list-faculties - list all faculties across the whole university in such format: <id> <name>"},
    {"add-student", cmd_add_student, "add-student <id> <name> - add a student into the global doubly linked list"},
    {"remove-student", cmd_remove_student, "remove-student <id> - remove a student from the global doubly linked list"},
    {"list-students", cmd_list_students, "list-students - list all students across the whole university; format: <id> <name>"},
    {"student-list-groups", cmd_student_list_groups, "student-list-groups <student_id> - list groups of a particualar student"},
    {"faculty-add-group", cmd_add_group, "faculty-add-group <faculty_id> <group_id> <group_name> - add group into a particular faculty"},
    {"faculty-remove-group", cmd_remove_group, "faculty-remove-group <faculty_id> <group_id> - remove group from a particular faculty"},
    {"faculty-list-groups", cmd_faculty_list_groups, "faculty-list-groups <faculty_id> - list all groups that belong to a particular faculty in such format: <id> <name>"},
    {"group-list-students", cmd_group_list_students, "group-list-students <group_id>"},
    {"enroll", cmd_enroll, "enroll <student_id> <group_id>"},
    {"unenroll", cmd_unenroll, "unenroll <student_id> <group_id>"},
    {"uni-info", cmd_uni_info, "uni-info - print short summary of the university"},
    {"uni-rename", cmd_uni_rename, "uni-rename <name> - set the naem of the university (default: Vilnius Tech)"},
    {"quit", cmd_quit, "quit - exit the REPL"},
    {"help", cmd_help, "help - list all commands or help [command] - print format of the command"}
};

static size_t n_commands = sizeof(commands) / sizeof(Command);

static int cmd_help(App *a, int argc, char **argv)
{
    (void)a;
    if (argc < 1)
    {
        printf("%s\n", "Available commands");
        for (size_t i = 0; i < n_commands; i++)
            printf(" %-15s\n", commands[i].name);
    } else 
        for (size_t j = 0; j < n_commands; j++)
            if (strcmp(argv[0], commands[j].name) == OK) 
            {
                printf("%s\n", commands[j].help_field);
                break;
            }
    return OK;
}

static int dispatch_commands(App *a, int argc, char **argv)
{
    if (argc == 0)
        return 0;

    for (size_t i = 0; i < n_commands; i++)
    {
        if (strcmp(argv[0], commands[i].name) == OK)
        {
            return commands[i].fn(a, argc - 1, argv + 1);
        }
    }
    printf("Unknown command: %s\n", argv[0]);
    return 1;
}

void cli_run(App *a)
{
    char line[256];
    char *argv[16];
    printf("%s\n", "Type 'help' to see the list of commands or 'help [command]' to see the command's format.");
    printf("%s\n", "Type 'quit' to exit.");
    for (;;)
    {
        printf("%s", "> ");
        if (fgets(line, sizeof(line) / sizeof(char), stdin) == NULL)
            break;
        
        size_t first_new_line_idx = strcspn(line, "\n");
        line[first_new_line_idx] = '\0';
        int argc = tokenizer(line, argv, (int)(sizeof(argv) / sizeof(char *)));
        int dispatcher = dispatch_commands(a, argc, argv);

        if (dispatcher == QUIT)
            break;
    }
}

