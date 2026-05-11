#include "test_s21_insert.h"

#include "../string/s21_string.h"

START_TEST(test_insert_single_in_the_beginning) {
  const char *str1 = "ello";
  const char *str2 = "H";
  char *res_s21 = s21_insert(str1, str2, 0);
  const char *res_std = "Hello";
  ck_assert_str_eq(res_s21, res_std);
  if (res_s21) free(res_s21);
}
END_TEST

START_TEST(test_insert_multiple_in_the_beginning) {
  const char *str1 = "lo";
  const char *str2 = "Hel";
  char *res_s21 = s21_insert(str1, str2, 0);
  const char *res_std = "Hello";
  ck_assert_str_eq(res_s21, res_std);
  if (res_s21) free(res_s21);
}
END_TEST

START_TEST(test_insert_single_in_the_end) {
  const char *str1 = "Hell";
  const char *str2 = "o";
  char *res_s21 = s21_insert(str1, str2, 4);
  const char *res_std = "Hello";
  ck_assert_str_eq(res_s21, res_std);
  if (res_s21) free(res_s21);
}
END_TEST

START_TEST(test_insert_multiple_in_the_end) {
  const char *str1 = "He";
  const char *str2 = "llo";
  char *res_s21 = s21_insert(str1, str2, 2);
  const char *res_std = "Hello";
  ck_assert_str_eq(res_s21, res_std);
  if (res_s21) free(res_s21);
}
END_TEST

START_TEST(test_insert_single_in_the_middle) {
  const char *str1 = "Lorem ipsum door sit amet";
  const char *str2 = "l";
  char *res_s21 = s21_insert(str1, str2, 14);
  const char *res_std = "Lorem ipsum dolor sit amet";
  ck_assert_str_eq(res_s21, res_std);
  if (res_s21) free(res_s21);
}
END_TEST

START_TEST(test_insert_multiple_in_the_middle) {
  const char *str1 = "Lorem ipsum  sit amet";
  const char *str2 = "dolor";
  char *res_s21 = s21_insert(str1, str2, 12);
  const char *res_std = "Lorem ipsum dolor sit amet";
  ck_assert_str_eq(res_s21, res_std);
  if (res_s21) free(res_s21);
}
END_TEST

START_TEST(test_insert_empty_in_the_beginning) {
  const char *str1 = "Lorem ipsum  sit amet";
  const char *str2 = "";
  char *res_s21 = s21_insert(str1, str2, 0);
  const char *res_std = "Lorem ipsum  sit amet";
  ck_assert_str_eq(res_s21, res_std);
  if (res_s21) free(res_s21);
}
END_TEST

START_TEST(test_insert_empty_in_the_end) {
  const char *str1 = "Lorem ipsum  sit amet";
  const char *str2 = "";
  char *res_s21 = s21_insert(str1, str2, 21);
  const char *res_std = "Lorem ipsum  sit amet";
  ck_assert_str_eq(res_s21, res_std);
  if (res_s21) free(res_s21);
}
END_TEST

START_TEST(test_insert_empty_in_the_middle) {
  const char *str1 = "Lorem ipsum  sit amet";
  const char *str2 = "";
  char *res_s21 = s21_insert(str1, str2, 12);
  const char *res_std = "Lorem ipsum  sit amet";
  ck_assert_str_eq(res_s21, res_std);
  if (res_s21) free(res_s21);
}
END_TEST

START_TEST(test_insert_empty_in_empty) {
  const char *str1 = "";
  const char *str2 = "";
  char *res_s21 = s21_insert(str1, str2, 0);
  const char *res_std = "";
  ck_assert_str_eq(res_s21, res_std);
  if (res_s21) free(res_s21);
}
END_TEST

START_TEST(test_insert_OOB) {
  const char *str1 = "Some string";
  const char *str2 = "is here";
  char *res_s21 = s21_insert(str1, str2, 12);
  const char *res_std = S21_NULL;
  ck_assert_pstr_eq(res_s21, res_std);
  if (res_s21) free(res_s21);
}
END_TEST

START_TEST(test_insert_OOB_2) {
  const char *str1 = "";
  const char *str2 = "is here";
  char *res_s21 = s21_insert(str1, str2, 100);
  const char *res_std = S21_NULL;
  ck_assert_pstr_eq(res_s21, res_std);
  if (res_s21) free(res_s21);
}
END_TEST

START_TEST(test_insert_OOB_3) {
  const char *str1 = "is here";
  const char *str2 = "";
  char *res_s21 = s21_insert(str1, str2, 100);
  const char *res_std = S21_NULL;
  ck_assert_pstr_eq(res_s21, res_std);
  if (res_s21) free(res_s21);
}
END_TEST

Suite *s21_insert_suite(void) {
  Suite *s = suite_create("s21_insert");
  TCase *tc_core = tcase_create("Core");
  tcase_add_test(tc_core, test_insert_single_in_the_beginning);
  tcase_add_test(tc_core, test_insert_multiple_in_the_beginning);
  tcase_add_test(tc_core, test_insert_single_in_the_end);
  tcase_add_test(tc_core, test_insert_multiple_in_the_end);
  tcase_add_test(tc_core, test_insert_single_in_the_middle);
  tcase_add_test(tc_core, test_insert_multiple_in_the_middle);
  tcase_add_test(tc_core, test_insert_empty_in_the_beginning);
  tcase_add_test(tc_core, test_insert_empty_in_the_end);
  tcase_add_test(tc_core, test_insert_empty_in_the_middle);
  tcase_add_test(tc_core, test_insert_empty_in_empty);
  tcase_add_test(tc_core, test_insert_OOB);
  tcase_add_test(tc_core, test_insert_OOB_2);
  tcase_add_test(tc_core, test_insert_OOB_3);

  suite_add_tcase(s, tc_core);
  return s;
}
