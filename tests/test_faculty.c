#include "result.h"
#include "university.h"
#include "faculty.h"
#include "group.h"
#include <check.h>

static University *u;
static Faculty *f;
static Group *g1, *g2;

static void setup(void)
{
	f = faculty_create(100, "F1");
    g1 = group_create(10, "EIfu-23");
    g2 = group_create(11, "ISKfu-23");
}

static void destroy(void) 
{
	university_destroy(u);
}

START_TEST(add_groups)
{
	/* unit test code */
	ck_assert_int_eq(faculty_add_group(u, f, g1), OK);
	ck_assert_int_eq(faculty_add_group(u, f, g2), OK);
	ck_assert_int_eq(f->group_count, 2);
}
END_TEST

START_TEST(test_duplicates)
{
	/* unit test code */
	ck_assert_int_eq(faculty_add_group(u, f, g1), OK);
	ck_assert_int_eq(faculty_add_group(u, f, g1), ERR);
	ck_assert_int_eq(f->group_count, 1);
}
END_TEST

START_TEST(remove_groups)
{
	/* unit test code */
	ck_assert_int_eq(faculty_add_group(u, f, g1), OK);
	ck_assert_int_eq(faculty_add_group(u, f, g2), OK);
	ck_assert_int_eq(f->group_count, 2);
    ck_assert_int_eq(faculty_remove_group(f, g2), OK);
    ck_assert_int_eq(f->group_count, 1);
    ck_assert_int_eq(faculty_remove_group(f, g1), OK);
    ck_assert_int_eq(f->group_count, 0);
}
END_TEST

Suite *faculty_suite(void) 
{
	Suite *suite = suite_create("faculty");
	TCase *tc = tcase_create("case");
	tcase_add_checked_fixture(tc, setup, destroy);

	tcase_add_test(tc, add_groups);
	tcase_add_test(tc, test_duplicates);
	tcase_add_test(tc, remove_groups);

	suite_add_tcase(suite, tc);
	return suite;
}

int main(void)
{
	SRunner *sr = srunner_create(faculty_suite());
	srunner_run_all(sr, CK_NORMAL);
	int failed = srunner_ntests_failed(sr);
	srunner_free(sr);
	return failed ? ERR : OK;
}

