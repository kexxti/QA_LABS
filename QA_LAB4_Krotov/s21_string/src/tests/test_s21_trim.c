#include "test_s21_trim.h"

START_TEST(test_trim_empty) {
  const char *str1 = " Hello, World! ";
  const char *str2 = " ";
  char *res_s21 = s21_trim(str1, str2);
  const char *res_std = "Hello, World!";
  ck_assert_str_eq(res_s21, res_std);
  if (res_s21) free(res_s21);
}
END_TEST

START_TEST(test_trim_symbols) {
  const char *str1 = "!!!Hello!!!";
  const char *str2 = "!";
  char *res_s21 = s21_trim(str1, str2);
  const char *res_std = "Hello";
  ck_assert_str_eq(res_s21, res_std);
  if (res_s21) free(res_s21);
}
END_TEST

START_TEST(test_trim_full_trim) {
  const char *str1 = "#####";
  const char *str2 = "#";
  char *res_s21 = s21_trim(str1, str2);
  const char *res_std = "";
  ck_assert_str_eq(res_s21, res_std);
  if (res_s21) free(res_s21);
}
END_TEST

START_TEST(test_trim_rus) {
  const char *str1 = "  Привет, мир!  ";
  const char *str2 = " ";
  char *res_s21 = s21_trim(str1, str2);
  const char *res_std = "Привет, мир!";
  ck_assert_str_eq(res_s21, res_std);
  if (res_s21) free(res_s21);
}
END_TEST

START_TEST(test_trim_null_src) {
  const char *str1 = S21_NULL;
  const char *str2 = " ";
  char *res_s21 = s21_trim(str1, str2);
  ck_assert_ptr_null(res_s21);
}
END_TEST

START_TEST(test_trim_null_trim_chars) {
  const char *str1 = "Hello, World!";
  const char *str2 = NULL;
  char *res_s21 = s21_trim(str1, str2);
  ck_assert_ptr_null(res_s21);
}
END_TEST

START_TEST(test_trim_long) {
  const char *str1 = "**********Hello, World!**********";
  const char *str2 = "*";
  char *res_s21 = s21_trim(str1, str2);
  const char *res_std = "Hello, World!";
  ck_assert_str_eq(res_s21, res_std);
  if (res_s21) free(res_s21);
}
END_TEST

START_TEST(test_trim_empty_src) {
  const char *str1 = "";
  const char *str2 = " ";
  char *res_s21 = s21_trim(str1, str2);
  const char *res_std = "";
  ck_assert_str_eq(res_s21, res_std);
  if (res_s21) free(res_s21);
}
END_TEST

START_TEST(test_trim_empty_trim_chars) {
  const char *str1 = " Hello, World! ";
  const char *str2 = "";
  char *res_s21 = s21_trim(str1, str2);
  const char *res_std = " Hello, World! ";
  ck_assert_str_eq(res_s21, res_std);
  if (res_s21) free(res_s21);
}
END_TEST

START_TEST(test_trim_all_trim_chars) {
  const char *str1 = "*****";
  const char *str2 = "*";
  char *res_s21 = s21_trim(str1, str2);
  const char *res_std = "";
  ck_assert_str_eq(res_s21, res_std);
  if (res_s21) free(res_s21);
}
END_TEST

START_TEST(test_trim_inner_chars_untouched) {
  const char *str1 = "**Hello**World**";
  const char *str2 = "*";
  char *res_s21 = s21_trim(str1, str2);
  const char *res_std = "Hello**World";
  ck_assert_str_eq(res_s21, res_std);
  if (res_s21) free(res_s21);
}
END_TEST

START_TEST(test_trim_single_char) {
  const char *str1 = "a";
  const char *str2 = "a";
  char *res_s21 = s21_trim(str1, str2);
  const char *res_std = "";
  ck_assert_str_eq(res_s21, res_std);
  if (res_s21) free(res_s21);
}
END_TEST

START_TEST(test_trim_whitespace_chars) {
  const char *str1 = "\t\n Hello, World! \n\t";
  const char *str2 = " \t\n";
  char *res_s21 = s21_trim(str1, str2);
  const char *res_std = "Hello, World!";
  ck_assert_str_eq(res_s21, res_std);
  if (res_s21) free(res_s21);
}
END_TEST

START_TEST(test_trim_large_trim_chars) {
  const char *str1 = "#$%Hello, World!#$%";
  const char *str2 = "!@#$%^&*()";
  char *res_s21 = s21_trim(str1, str2);
  const char *res_std = "Hello, World";
  ck_assert_str_eq(res_s21, res_std);
  if (res_s21) free(res_s21);
}
END_TEST

START_TEST(test_trim_multiline) {
  const char *str1 = "\n\nHello, World!\n\n";
  const char *str2 = "\n";
  char *res_s21 = s21_trim(str1, str2);
  const char *res_std = "Hello, World!";
  ck_assert_str_eq(res_s21, res_std);
  if (res_s21) free(res_s21);
}
END_TEST

Suite *s21_trim_suite(void) {
  Suite *s = suite_create("s21_trim");
  TCase *tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_trim_empty);
  tcase_add_test(tc_core, test_trim_symbols);
  tcase_add_test(tc_core, test_trim_full_trim);
  tcase_add_test(tc_core, test_trim_rus);
  tcase_add_test(tc_core, test_trim_null_src);
  tcase_add_test(tc_core, test_trim_null_trim_chars);
  tcase_add_test(tc_core, test_trim_long);
  tcase_add_test(tc_core, test_trim_empty_src);
  tcase_add_test(tc_core, test_trim_empty_trim_chars);
  tcase_add_test(tc_core, test_trim_all_trim_chars);
  tcase_add_test(tc_core, test_trim_inner_chars_untouched);
  tcase_add_test(tc_core, test_trim_single_char);
  tcase_add_test(tc_core, test_trim_whitespace_chars);
  tcase_add_test(tc_core, test_trim_large_trim_chars);
  tcase_add_test(tc_core, test_trim_multiline);

  suite_add_tcase(s, tc_core);
  return s;
}
