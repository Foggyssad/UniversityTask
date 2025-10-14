#include "result.h"
#include "university.h"
#include "faculty.h"
#include "group.h"
#include <check.h>


static University *u = NULL;
static Faculty *f  = NULL;

static void setup(void)
{
    u = university_create("TestU");
    ck_assert_ptr_nonnull(u);

    f = faculty_create(100, "F1");
    ck_assert_ptr_nonnull(f);

    ck_assert_int_eq(university_add_faculty(u, f), OK);
}

static void destroy(void)
{
    university_destroy(u);
    u = NULL;
    f = NULL;
}

static Group *make_group(int id, const char *name)
{
    Group *g = group_create(id, name);
    ck_assert_ptr_nonnull(g);
    return g;
}

START_TEST(test_add_groups)
{
	/* unit test code */
	Group *g1 = make_group(10, "EIfu-23");
	Group *g2 = make_group(11, "ISKfu-23");

	ck_assert_int_eq(faculty_add_group(u, f, g1), OK);
	ck_assert_int_eq(faculty_add_group(u, f, g2), OK);
	ck_assert_int_eq((int)f->group_count, 2);
}
END_TEST

START_TEST(test_group_duplicates_callee_frees)
{
	/* unit test code */
	Group *g1 = make_group(10, "EIfu-23");

	ck_assert_int_eq(faculty_add_group(u, f, g1), OK);
	ck_assert_int_eq(faculty_add_group(u, f, g1), ERR);
	ck_assert_int_eq(f->group_count, 1);
}
END_TEST

START_TEST(test_across_faculty_group_duplicates_callee_frees)
{
	/* unit test code */
	Faculty *f2 = faculty_create(200, "F2");
    ck_assert_ptr_nonnull(f2);
    ck_assert_int_eq(university_add_faculty(u, f2), OK);

    Group *g1 = make_group(42, "EIfu-23");
    Group *g2 = make_group(42, "ISKfu-23");

    ck_assert_int_eq(faculty_add_group(u, f2,  g1), OK);
    ck_assert_int_eq(faculty_add_group(u, f, g2), ERR);
    ck_assert_int_eq((int)f2->group_count, 1);
    ck_assert_int_eq((int)f->group_count, 0);
}
END_TEST

START_TEST(test_null_inputs)
{
    Group *g1 = make_group(43, "A");
    ck_assert_int_eq(faculty_add_group(NULL, f, g1), ERR);

    Group *g2 = make_group(44, "B");
    ck_assert_int_eq(faculty_add_group(u, NULL, g2), ERR);

    ck_assert_int_eq(faculty_add_group(u, f, NULL), ERR);
}
END_TEST

START_TEST(test_remove_groups)
{
	/* unit test code */
	Group *g1 = make_group(10, "EIfu-23");
    Group *g2 = make_group(11, "ISKfu-23");

    ck_assert_int_eq(faculty_add_group(u, f, g1), OK);
    ck_assert_int_eq(faculty_add_group(u, f, g2), OK);
    ck_assert_int_eq((int)f->group_count, 2);

    ck_assert_int_eq(faculty_remove_group(f, g2), OK);
    ck_assert_int_eq((int)f->group_count, 1);
    ck_assert_int_eq(faculty_remove_group(f, g1), OK);
    ck_assert_int_eq((int)f->group_count, 0);
}
END_TEST

Suite *faculty_suite(void) 
{
	Suite *suite = suite_create("faculty");
	TCase *tc = tcase_create("case");
	tcase_add_checked_fixture(tc, setup, destroy);

	tcase_add_test(tc, test_add_groups);
	tcase_add_test(tc, test_null_inputs);
	tcase_add_test(tc, test_group_duplicates_callee_frees);
	tcase_add_test(tc, test_across_faculty_group_duplicates_callee_frees);
	tcase_add_test(tc, test_remove_groups);

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

