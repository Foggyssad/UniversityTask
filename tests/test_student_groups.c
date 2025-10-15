#include "error_types.h"
#include "group.h"
#include "student.h"
#include <check.h>

static StudentList s_list;
static Student *s1, *s2;
static Group *g1, *g2;

static void setup(void)
{
	student_list_init(&s_list);
    s1 = student_add(&s_list, 1, "A");
    s2 = student_add(&s_list, 2, "B");
    g1 = group_create(10, "EIfu-23");
    g2 = group_create(11, "ISKfu-23");
}

static void destroy(void) 
{
	student_list_clear(&s_list);
    group_destroy(g1);
    group_destroy(g2);
}

static inline int enroll(Student *s, Group *g)
{
    return student_add_group(s, g);
}

static inline int leave(Student *s, Group *g)
{
    return student_remove_group(s, g);
}

START_TEST(add_group_bidirectional)
{
	/* unit test code */
	ck_assert_int_eq(enroll(s1, g1), OK);
    ck_assert_int_eq((int)s1->group_count, 1);
    ck_assert_ptr_eq(s1->groups[0], g1);

    ck_assert_int_eq((int)g1->student_count, 1);
    ck_assert_ptr_eq(g1->students[0], s1);
}
END_TEST

START_TEST(duplicate_test)
{
	/* unit test code */
    ck_assert_int_eq(enroll(s1, g1), OK);
    ck_assert_int_eq(enroll(s1, g1), OK);
    ck_assert_int_eq((int)s1->group_count, 1);
    ck_assert_int_eq((int)g1->student_count, 1);
}
END_TEST

START_TEST(add_two_groups_then_remove_one)
{
	/* unit test code */
    ck_assert_int_eq(enroll(s1, g1), OK);
    ck_assert_int_eq(enroll(s1, g2), OK);
    ck_assert_int_eq((int)s1->group_count, 2);
    ck_assert_int_eq((int)g1->student_count + (int)g2->student_count, 2);

    ck_assert_int_eq(leave(s1, g1), OK);
    ck_assert_int_eq(s1->group_count, 1);
    ck_assert_int_eq(g1->student_count, 0);
    ck_assert_int_eq(g2->student_count, 1);
    ck_assert_ptr_eq(g2->students[0], s1);
}
END_TEST

Suite *student_groups_suite(void) 
{
	Suite *suite = suite_create("student_groups");
	TCase *tc = tcase_create("case");
	tcase_add_checked_fixture(tc, setup, destroy);

	tcase_add_test(tc, add_group_bidirectional);
	tcase_add_test(tc, duplicate_test);
	tcase_add_test(tc, add_two_groups_then_remove_one);
	suite_add_tcase(suite, tc);
	return suite;
}

int main(void)
{
	SRunner *sr = srunner_create(student_groups_suite());
	srunner_run_all(sr, CK_NORMAL);
	int failed = srunner_ntests_failed(sr);
	srunner_free(sr);
	return failed ? ERR : OK;
}