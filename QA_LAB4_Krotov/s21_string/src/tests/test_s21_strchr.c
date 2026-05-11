#include "test_s21_strchr.h"

#include "../string/s21_string.h"

START_TEST(test_strchr_char_in_beginning) {
  const char str[] = "Hello";
  int c = 'H';
  char *res_s21 = s21_strchr(str, c);
  char *res_std = strchr(str, c);
  ck_assert_ptr_eq(res_s21, res_std);
}
END_TEST

START_TEST(test_strchr_char_in_middle) {
  const char str[] = "Hello, world!";
  int c = 'o';
  char *res_s21 = s21_strchr(str, c);
  char *res_std = strchr(str, c);
  ck_assert_ptr_eq(res_s21, res_std);
}
END_TEST

START_TEST(test_strchr_char_in_end) {
  const char str[] =
      "rldrldrldrldrldrldrldrldrlrldrldrldrldrldrldrldrldrldrldrldrldrldrldrldr"
      "ldrldrldrldrldHello";
  int c = 'o';
  char *res_s21 = s21_strchr(str, c);
  char *res_std = strchr(str, c);
  ck_assert_ptr_eq(res_s21, res_std);
}
END_TEST

START_TEST(test_strchr_char_not_found) {
  const char str[] = "Hello";
  int c = 'X';
  char *res_s21 = s21_strchr(str, c);
  char *res_std = strchr(str, c);
  ck_assert_ptr_eq(res_s21, res_std);
}
END_TEST

START_TEST(test_strchr_end_of_string) {
  const char str[] =
      "rldrldrldrldrldrldrldrldrlrldrldrldrldrldrldrldrldrldrldrldrldrldrldrldr"
      "ldrldrldrldrldHello";
  int c = '\0';
  char *res_s21 = s21_strchr(str, c);
  char *res_std = strchr(str, c);
  ck_assert_ptr_eq(res_s21, res_std);
}
END_TEST

START_TEST(test_strchr_empty_string) {
  const char str[] = "";
  int c = 'H';
  char *res_s21 = s21_strchr(str, c);
  char *res_std = strchr(str, c);
  ck_assert_ptr_eq(res_s21, res_std);
}
END_TEST

START_TEST(test_strchr_empty_string_end_of_string) {
  const char str[] = "";
  int c = '\0';
  char *res_s21 = s21_strchr(str, c);
  char *res_std = strchr(str, c);
  ck_assert_ptr_eq(res_s21, res_std);
}
END_TEST

START_TEST(test_strchr_lower_case) {
  const char str[] = "Hello";
  int c = 'h';
  char *res_s21 = s21_strchr(str, c);
  char *res_std = strchr(str, c);
  ck_assert_ptr_eq(res_s21, res_std);
}
END_TEST

Suite *s21_strchr_suite(void) {
  Suite *s = suite_create("s21_strchr");
  TCase *tc_core = tcase_create("Core");
  tcase_add_test(tc_core, test_strchr_char_in_beginning);
  tcase_add_test(tc_core, test_strchr_char_in_middle);
  tcase_add_test(tc_core, test_strchr_char_in_end);
  tcase_add_test(tc_core, test_strchr_char_not_found);
  tcase_add_test(tc_core, test_strchr_end_of_string);
  tcase_add_test(tc_core, test_strchr_empty_string);
  tcase_add_test(tc_core, test_strchr_empty_string_end_of_string);
  tcase_add_test(tc_core, test_strchr_lower_case);
  suite_add_tcase(s, tc_core);
  return s;
}
