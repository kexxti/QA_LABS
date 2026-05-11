#include "test_s21_strncpy.h"

#include "../string/s21_string.h"

START_TEST(copy_exact_length) {
  int n = 12;
  char s21_dest[13] = "!S21_School!";
  char dest[13] = "!S21_School!";
  char src[13] = "Hello World!";
  ck_assert_str_eq(s21_strncpy(s21_dest, src, n), strncpy(dest, src, n));
}
END_TEST

START_TEST(copy_with_truncation) {
  int n = 6;
  char s21_dest[7] = "School";
  char dest[7] = "School";
  char src[13] = "Hello World!";
  ck_assert_str_eq(s21_strncpy(s21_dest, src, n), strncpy(dest, src, n));
}
END_TEST

START_TEST(copy_with_zeros) {
  int n = 15;
  char s21_dest[16] = "S21_School_Best";
  char dest[16] = "S21_School_Best";
  char src[13] = "Hello World!";
  ck_assert_str_eq(s21_strncpy(s21_dest, src, n), strncpy(dest, src, n));
}
END_TEST

START_TEST(empty_src) {
  int n = 5;
  char s21_dest[6] = "12345";
  char dest[6] = "12345";
  char src[1] = "";
  ck_assert_str_eq(s21_strncpy(s21_dest, src, n), strncpy(dest, src, n));
}
END_TEST

START_TEST(copy_into_empty_dest) {
  int n = 5;
  char s21_dest[6] = "";
  char dest[6] = "";
  char src[5] = "Hello";
  ck_assert_str_eq(s21_strncpy(s21_dest, src, n), strncpy(dest, src, n));
}
END_TEST

START_TEST(copy_empty_string_to_empty_dest) {
  int n = 0;
  char s21_dest[1] = "";
  char dest[1] = "";
  char src[1] = "";
  ck_assert_str_eq(s21_strncpy(s21_dest, src, n), strncpy(dest, src, n));
}
END_TEST

START_TEST(last_test) {
  int n = 12;
  char s21_dest[13] = "!S21_School!";
  char dest[13] = "!S21_School!";
  char src[13] = "Hello World!";
  src[3] = '\0';
  ck_assert_str_eq(s21_strncpy(s21_dest, src, n), strncpy(dest, src, n));
}
END_TEST

Suite *s21_strncpy_suite(void) {
  Suite *s = suite_create("s21_strncpy");
  TCase *tc_core = tcase_create("Core");
  tcase_add_test(tc_core, copy_exact_length);
  tcase_add_test(tc_core, copy_with_truncation);
  tcase_add_test(tc_core, copy_with_zeros);
  tcase_add_test(tc_core, empty_src);
  tcase_add_test(tc_core, copy_into_empty_dest);
  tcase_add_test(tc_core, copy_empty_string_to_empty_dest);
  tcase_add_test(tc_core, last_test);

  suite_add_tcase(s, tc_core);
  return s;
}
