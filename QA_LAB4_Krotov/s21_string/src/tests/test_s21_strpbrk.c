#include "test_s21_strpbrk.h"

START_TEST(test_default_pointer) {
  char* str1 = "Hello, World!";
  char* str2 = "Look at this World!";
  char* res_s21 = s21_strpbrk(str1, str2);
  char* res_std = strpbrk(str1, str2);
  ck_assert_ptr_eq(res_s21, res_std);
}
END_TEST

START_TEST(test_complex_pointer) {
  char* str1 = "Hello, World!";
  char* str2 = "aaaawwww!!,,";
  char* res_s21 = s21_strpbrk(str1, str2);
  char* res_std = strpbrk(str1, str2);
  ck_assert_ptr_eq(res_s21, res_std);
}
END_TEST

START_TEST(test_no_match) {
  char* str1 = "Hello!";
  char* str2 = "KYP";
  char* res_s21 = s21_strpbrk(str1, str2);
  char* res_std = strpbrk(str1, str2);
  ck_assert_ptr_eq(res_s21, res_std);
}
END_TEST

START_TEST(test_one_char) {
  char* str1 = "H";
  char* str2 = "H";
  char* res_s21 = s21_strpbrk(str1, str2);
  char* res_std = strpbrk(str1, str2);
  ck_assert_ptr_eq(res_s21, res_std);
}
END_TEST

START_TEST(test_empty_str1) {
  char* str1 = "";
  char* str2 = "H";
  char* res_s21 = s21_strpbrk(str1, str2);
  char* res_std = strpbrk(str1, str2);
  ck_assert_ptr_eq(res_s21, res_std);
}
END_TEST

START_TEST(test_empty_str2) {
  char* str1 = "!";
  char* str2 = "";
  char* res_s21 = s21_strpbrk(str1, str2);
  char* res_std = strpbrk(str1, str2);
  ck_assert_ptr_eq(res_s21, res_std);
}
END_TEST

START_TEST(test_empty_both) {
  char* str1 = "";
  char* str2 = "";
  char* res_s21 = s21_strpbrk(str1, str2);
  char* res_std = strpbrk(str1, str2);
  ck_assert_ptr_eq(res_s21, res_std);
}
END_TEST

START_TEST(test_one_char_non_match) {
  char* str1 = "?";
  char* str2 = "!";
  char* res_s21 = s21_strpbrk(str1, str2);
  char* res_std = strpbrk(str1, str2);
  ck_assert_ptr_eq(res_s21, res_std);
}
END_TEST

START_TEST(test_long_string_match) {
  char str1[100] = "aaaaaaaaaaaaaaaaaaaaaaaab";
  char* str2 = "b";
  char* res_s21 = s21_strpbrk(str1, str2);
  char* res_std = strpbrk(str1, str2);
  ck_assert_ptr_eq(res_s21, res_std);
}
END_TEST

Suite* s21_strpbrk_suite(void) {
  Suite* s = suite_create("s21_strpbrk");
  TCase* tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_default_pointer);
  tcase_add_test(tc_core, test_complex_pointer);
  tcase_add_test(tc_core, test_no_match);
  tcase_add_test(tc_core, test_one_char);
  tcase_add_test(tc_core, test_empty_str1);
  tcase_add_test(tc_core, test_empty_str2);
  tcase_add_test(tc_core, test_empty_both);
  tcase_add_test(tc_core, test_one_char_non_match);
  tcase_add_test(tc_core, test_long_string_match);

  suite_add_tcase(s, tc_core);
  return s;
}
