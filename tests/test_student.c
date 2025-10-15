#include "error_types.h"
#include "group.h"
#include "student.h"
#include <check.h>

static StudentList s_list;

static void setup(void)
{
	student_list_init(&s_list);
}

static void destroy(void) 
{
	student_list_clear(&s_list);
}

static void fill123(StudentList *s_list)
{
	Student *a = student_add(s_list, 1, "A");
	Student *b = student_add(s_list, 2, "B");
	Student *c = student_add(s_list, 3, "C");
}

START_TEST(add_push_back_keeps_order)
{
	/* unit test code */
	fill123(&s_list);

	ck_assert_int_eq((int)s_list.size, 3);
	ck_assert_int_eq(s_list.head->id, 1);
	ck_assert_int_eq(s_list.tail->id, 3);
	ck_assert_ptr_eq(s_list.head->next_node, s_list.tail->prev_node);
}
END_TEST

START_TEST(remove_head_on_three)
{
	/* unit test code */
	fill123(&s_list);
	ck_assert_int_eq(student_remove(&s_list, 1), OK);
	list_students(&s_list);
	ck_assert_int_eq((int)s_list.size, 2);
	ck_assert_int_eq(s_list.head->id, 2);
	ck_assert_ptr_null(s_list.head->prev_node);
}
END_TEST

START_TEST(remove_tail_on_three)
{
	/* unit test code */
	fill123(&s_list);
	ck_assert_int_eq(student_remove(&s_list, 3), OK);
	list_students(&s_list);
	ck_assert_int_eq((int)s_list.size, 2);
	ck_assert_int_eq(s_list.head->id, 1);
	ck_assert_ptr_null(s_list.tail->next_node);
}
END_TEST

START_TEST(remove_middle_on_three)
{
	/* unit test code */
	fill123(&s_list);
	ck_assert_int_eq(student_remove(&s_list, 2), OK);
	list_students(&s_list);
	ck_assert_int_eq((int)s_list.size, 2);
	ck_assert_int_eq(s_list.head->id, 1);
	ck_assert_ptr_eq(s_list.head->next_node, s_list.tail);
	ck_assert_ptr_eq(s_list.tail->prev_node, s_list.head);
}
END_TEST

START_TEST(remove_non_existent_returns_0)
{
	/* unit test code */
	fill123(&s_list);
	ck_assert_int_eq(student_remove(&s_list, 42), ERR);
	list_students(&s_list);
	ck_assert_int_eq((int)s_list.size, 3);
	ck_assert_int_eq(s_list.head->id, 1);
	ck_assert_int_eq(s_list.tail->id, 3);
}
END_TEST

START_TEST(find_returs_correct_node)
{
	/* unit test code */
	fill123(&s_list);
	Student *s2 = student_find(&s_list, 2);
	ck_assert_ptr_nonnull(s2);
	ck_assert_int_eq(s2->id, 2);
	ck_assert_ptr_null(student_find(&s_list, 42));
}
END_TEST

Suite *student_suite(void) 
{
	Suite *suite = suite_create("student");
	TCase *tc = tcase_create("case");
	tcase_add_checked_fixture(tc, setup, destroy);

	tcase_add_test(tc, add_push_back_keeps_order);
	tcase_add_test(tc, remove_head_on_three);
	tcase_add_test(tc, remove_tail_on_three);
	tcase_add_test(tc, remove_middle_on_three);
	tcase_add_test(tc, remove_non_existent_returns_0);
	tcase_add_test(tc, find_returs_correct_node);

	suite_add_tcase(suite, tc);
	return suite;
}

int main(void)
{
	SRunner *sr = srunner_create(student_suite());
	srunner_run_all(sr, CK_NORMAL);
	int failed = srunner_ntests_failed(sr);
	srunner_free(sr);
	return failed ? ERR : OK;
}