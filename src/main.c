#include "faculty.h"
#include "group.h"
#include "student.h"
#include "university.h"
#include "app.h"
#include "utils.h"
#include "cli.h"
#include "error_types.h"

#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	App app;
	app_init(&app, "Vilnius Tech");
	
	cli_run(&app);
	app_destroy(&app);

	return OK;
}