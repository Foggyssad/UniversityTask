#include "result.h"
#include "university.h"
#include "faculty.h"
#include <check.h>

static University *u = NULL;

static void setup(void)
{
	u = university_create("TestU");
	ck_assert_ptr_nonnull(u);
}

static void destroy(void) 
{
	university_destroy(u);
	u = NULL;
}

static Faculty *make_faculty(int id, const char *name)
{
	Faculty *f = faculty_create(id, name);
	ck_assert_ptr_nonnull(f);
	return f;
}

static Group *make_group(int id, const char *name)
{
	Group *g = group_create(id, name);
	ck_assert_ptr_nonnull(g);
	return g;
}

START_TEST(add_faculties)
{
	/* unit test code */
	Faculty *f = make_faculty(100, "Elec");
	ck_assert_int_eq(university_add_faculty(u, f), OK);
	ck_assert_int_eq((int)u->faculty_count, 1);
	ck_assert_ptr_eq(university_find_faculty(u, 100), f);
}
END_TEST

START_TEST(test_faculty_duplicates_callee_frees)
{
    Faculty *f1 = make_faculty(100, "Elec");
	Faculty *f2 = make_faculty(100, "Fund");
	ck_assert_int_eq(university_add_faculty(u, f1), OK);
    ck_assert_int_eq(university_add_faculty(u, f2), ERR);
    ck_assert_int_eq((int)u->faculty_count, 1);
    ck_assert_ptr_eq(university_find_faculty(u, 100), f1);
}
END_TEST

START_TEST(test_group_duplicates_callee_frees)
{
    Faculty *f1 = make_faculty(100, "Elec");
	Faculty *f2 = make_faculty(101, "Fund");
	ck_assert_int_eq(university_add_faculty(u, f1), OK);
    ck_assert_int_eq(university_add_faculty(u, f2), OK);
	Group *g1 = make_group(10, "EIfu-23");
	Group *g2 = make_group(10, "ISKfu-23");

	ck_assert_int_eq(faculty_add_group(u, f1, g1), OK);
	ck_assert_int_eq(faculty_add_group(u, f2, g2), ERR);
}
END_TEST

START_TEST(test_null_inputs)
{
    Faculty *f1 = make_faculty(100, "Elec");
	ck_assert_int_eq(university_add_faculty(NULL, f1), ERR);
	ck_assert_int_eq(university_add_faculty(u, NULL), ERR);
}
END_TEST

START_TEST(remove_faculties)
{
	/* unit test code */
	Faculty *f1 = make_faculty(100, "Elec");
	Faculty *f2 = make_faculty(101, "Fund");
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
	tcase_add_test(tc, test_null_inputs);
	tcase_add_test(tc, test_faculty_duplicates_callee_frees);
	tcase_add_test(tc, test_group_duplicates_callee_frees);
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
	return failed ? ERR : OK;
}

