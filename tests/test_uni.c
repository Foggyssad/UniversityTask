#include "result.h"
#include "university.h"
#include "faculty.h"
#include <check.h>

static University *u;
static Faculty *f1, *f2;

static void setup(void)
{
	u = university_create("Vilnius Tech");
    f1 = faculty_create(100, "Electronics");
    f2 = faculty_create(101, "Fundamental Sciences");
}

static void destroy(void) 
{
	university_destroy(u);
}

START_TEST(add_faculties)
{
	/* unit test code */
	ck_assert_int_eq(university_add_faculty(u, f1), OK);
	ck_assert_int_eq(university_add_faculty(u, f2), OK);
	ck_assert_int_eq(u->faculty_count, 2);
}
END_TEST

START_TEST(test_duplicates)
{
	/* unit test code */
    ck_assert_int_eq(university_add_faculty(u, f1), OK);
	ck_assert_int_eq(university_add_faculty(u, f1), ERR);
	ck_assert_int_eq(u->faculty_count, 1);
}
END_TEST

START_TEST(remove_faculties)
{
	/* unit test code */
    ck_assert_int_eq(university_add_faculty(u, f1), OK);
	ck_assert_int_eq(university_add_faculty(u, f2), OK);
	ck_assert_int_eq(u->faculty_count, 2);
    ck_assert_int_eq(university_remove_faculty(u, f2), OK);
    ck_assert_int_eq(u->faculty_count, 1);
    ck_assert_int_eq(university_remove_faculty(u, f1), OK);
    ck_assert_int_eq(u->faculty_count, 0);
}
END_TEST

Suite *university_suite(void) 
{
	Suite *suite = suite_create("university");
	TCase *tc = tcase_create("case");
	tcase_add_checked_fixture(tc, setup, destroy);

	tcase_add_test(tc, add_faculties);
	tcase_add_test(tc, test_duplicates);
	tcase_add_test(tc, remove_faculties);

	suite_add_tcase(suite, tc);
	return suite;
}

int main(void)
{
	SRunner *sr = srunner_create(university_suite());
	srunner_run_all(sr, CK_NORMAL);
	int failed = srunner_ntests_failed(sr);
	srunner_free(sr);
	return failed ? OK : ERR;
}

