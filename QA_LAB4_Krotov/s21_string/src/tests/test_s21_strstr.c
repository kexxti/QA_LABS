#include "test_s21_strstr.h"

#include "../string/s21_string.h"

START_TEST(test_empty_needle) {
  const char *haystack = "Hello, world!";
  const char *needle = "";
  char *s21_result = s21_strstr(haystack, needle);
  char *result = strstr(haystack, needle);
  ck_assert_ptr_eq(s21_result, result);
}
END_TEST

START_TEST(test_needle_not_found) {
  const char *haystack = "Hello, world!";
  const char *needle = "Goodbye";
  char *s21_result = s21_strstr(haystack, needle);
  char *result = strstr(haystack, needle);
  ck_assert_ptr_eq(s21_result, result);
}
END_TEST

START_TEST(test_needle_found_at_start) {
  const char *haystack = "Hello, world!";
  const char *needle = "Hello";
  char *s21_result = s21_strstr(haystack, needle);
  char *result = strstr(haystack, needle);
  ck_assert_ptr_eq(s21_result, result);
}
END_TEST

START_TEST(test_needle_found_at_end) {
  const char *haystack = "Hello, world!";
  const char *needle = "world!";
  char *s21_result = s21_strstr(haystack, needle);
  char *result = strstr(haystack, needle);
  ck_assert_ptr_eq(s21_result, result);
}
END_TEST

START_TEST(test_needle_found_in_middle) {
  const char *haystack = "Hello, world!";
  const char *needle = "lo, w";
  char *s21_result = s21_strstr(haystack, needle);
  char *result = strstr(haystack, needle);
  ck_assert_ptr_eq(s21_result, result);
}
END_TEST

START_TEST(test_identical_strings) {
  const char *haystack = "identical";
  const char *needle = "identical";
  char *s21_result = s21_strstr(haystack, needle);
  char *result = strstr(haystack, needle);
  ck_assert_ptr_eq(s21_result, result);
}
END_TEST

START_TEST(test_haystack_empty) {
  const char *haystack = "";
  const char *needle = "Hello";
  char *s21_result = s21_strstr(haystack, needle);
  char *result = strstr(haystack, needle);
  ck_assert_ptr_eq(s21_result, result);
}
END_TEST

START_TEST(test_needle_longer_than_haystack) {
  const char *haystack = "Hello";
  const char *needle = "Hello, world!";
  char *s21_result = s21_strstr(haystack, needle);
  char *result = strstr(haystack, needle);
  ck_assert_ptr_eq(s21_result, result);
}
END_TEST

Suite *s21_strstr_suite(void) {
  Suite *s = suite_create("s21_strstr");
  TCase *tc_core = tcase_create("Core");
  tcase_add_test(tc_core, test_empty_needle);
  tcase_add_test(tc_core, test_needle_not_found);
  tcase_add_test(tc_core, test_needle_found_at_start);
  tcase_add_test(tc_core, test_needle_found_at_end);
  tcase_add_test(tc_core, test_needle_found_in_middle);
  tcase_add_test(tc_core, test_identical_strings);
  tcase_add_test(tc_core, test_haystack_empty);
  tcase_add_test(tc_core, test_needle_longer_than_haystack);
  suite_add_tcase(s, tc_core);
  return s;
}
