#include "test_s21_strncmp.h"

START_TEST(test_basic_case) {
  char *str1 = "ABCD";
  char *str2 = "ABCJ";
  s21_size_t n = 3;
  int res_s21 = s21_strncmp(str1, str2, n);
  int res_std = strncmp(str1, str2, n);
  ck_assert_int_eq(res_s21, res_std);
}
END_TEST

START_TEST(test_full_match) {
  char *str1 = "ABCD";
  char *str2 = "ABCD";
  s21_size_t n = 4;
  int res_s21 = s21_strncmp(str1, str2, n);
  int res_std = strncmp(str1, str2, n);
  ck_assert_int_eq(res_s21, res_std);
}
END_TEST

START_TEST(test_partial_match) {
  char *str1 = "ABCD123";
  char *str2 = "ABCD";
  s21_size_t n = 4;
  int res_s21 = s21_strncmp(str1, str2, n);
  int res_std = strncmp(str1, str2, n);
  ck_assert_int_eq(res_s21, res_std);
}
END_TEST

START_TEST(test_mismatch) {
  char *str1 = "ABCD";
  char *str2 = "EFGH";
  s21_size_t n = 4;
  int res_s21 = s21_strncmp(str1, str2, n);
  int res_std = strncmp(str1, str2, n);
  ck_assert_int_lt(res_s21, 0);
  ck_assert_int_lt(res_std, 0);
}
END_TEST

START_TEST(test_empty_str1) {
  char *str1 = "";
  char *str2 = "ABCD";
  s21_size_t n = 4;
  int res_s21 = s21_strncmp(str1, str2, n);
  int res_std = strncmp(str1, str2, n);
  ck_assert_int_lt(res_s21, 0);
  ck_assert_int_lt(res_std, 0);
}
END_TEST

START_TEST(test_empty_str2) {
  char *str1 = "ABCX";
  char *str2 = "";
  s21_size_t n = 4;
  int res_s21 = s21_strncmp(str1, str2, n);
  int res_std = strncmp(str1, str2, n);
  ck_assert_int_gt(res_s21, 0);
  ck_assert_int_gt(res_std, 0);
}
END_TEST

START_TEST(test_empty_both) {
  char *str1 = "";
  char *str2 = "";
  s21_size_t n = 4;
  int res_s21 = s21_strncmp(str1, str2, n);
  int res_std = strncmp(str1, str2, n);
  ck_assert_int_eq(res_s21, res_std);
}
END_TEST

START_TEST(test_zero_cmp) {
  char *str1 = "S21_NULL";
  char *str2 = "S21_NULL";
  s21_size_t n = 0;
  int res_s21 = s21_strncmp(str1, str2, n);
  int res_std = strncmp(str1, str2, n);
  ck_assert_int_eq(res_s21, res_std);
}
END_TEST

START_TEST(test_extended_n) {
  char *str1 = "ABCD";
  char *str2 = "ABCD";
  s21_size_t n = 25;  // n больше длины строки
  int res_s21 = s21_strncmp(str1, str2, n);
  int res_std = strncmp(str1, str2, n);
  ck_assert_int_eq(res_s21, res_std);
}
END_TEST

START_TEST(test_case_sensitive) {
  char *str1 = "abcd";
  char *str2 = "ABCD";
  s21_size_t n = 4;
  int res_s21 = s21_strncmp(str1, str2, n);
  int res_std = strncmp(str1, str2, n);
  ck_assert_int_gt(res_s21, 0);
  ck_assert_int_gt(res_std, 0);
}
END_TEST

Suite *s21_strncmp_suite(void) {
  Suite *s = suite_create("s21_strncmp");
  TCase *tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_basic_case);
  tcase_add_test(tc_core, test_full_match);
  tcase_add_test(tc_core, test_partial_match);
  tcase_add_test(tc_core, test_mismatch);
  tcase_add_test(tc_core, test_empty_str1);
  tcase_add_test(tc_core, test_empty_str2);
  tcase_add_test(tc_core, test_empty_both);
  tcase_add_test(tc_core, test_zero_cmp);
  tcase_add_test(tc_core, test_extended_n);
  tcase_add_test(tc_core, test_case_sensitive);

  suite_add_tcase(s, tc_core);
  return s;
}
