#include "test_s21_strcspn.h"

#include "../string/s21_string.h"

START_TEST(test_strcspn_single_in_the_beginning) {
  const char *str1 = "Hello";
  const char *str2 = "H";
  s21_size_t res_s21 = s21_strcspn(str1, str2);
  s21_size_t res_std = (s21_size_t)strcspn(str1, str2);
  ck_assert_uint_eq(res_s21, res_std);
}
END_TEST

START_TEST(test_strcspn_single_in_the_middle) {
  const char *str1 = "Hello";
  const char *str2 = "e";
  s21_size_t res_s21 = s21_strcspn(str1, str2);
  s21_size_t res_std = (s21_size_t)strcspn(str1, str2);
  ck_assert_uint_eq(res_s21, res_std);
}
END_TEST

START_TEST(test_strcspn_single_in_the_end) {
  const char *str1 = "Hello";
  const char *str2 = "o";
  s21_size_t res_s21 = s21_strcspn(str1, str2);
  s21_size_t res_std = (s21_size_t)strcspn(str1, str2);
  ck_assert_uint_eq(res_s21, res_std);
}
END_TEST

START_TEST(test_strcspn_single_str2_multiple_in_the_middle) {
  const char *str1 = "Hello";
  const char *str2 = "l";
  s21_size_t res_s21 = s21_strcspn(str1, str2);
  s21_size_t res_std = (s21_size_t)strcspn(str1, str2);
  ck_assert_uint_eq(res_s21, res_std);
}
END_TEST

START_TEST(test_strcspn_multiple_in_the_beginning) {
  const char *str1 = "Hello";
  const char *str2 = "elH";
  s21_size_t res_s21 = s21_strcspn(str1, str2);
  s21_size_t res_std = (s21_size_t)strcspn(str1, str2);
  ck_assert_uint_eq(res_s21, res_std);
}
END_TEST

START_TEST(test_strcspn_empty_str2) {
  const char *str1 = "Hello";
  const char *str2 = "";
  s21_size_t res_s21 = s21_strcspn(str1, str2);
  s21_size_t res_std = (s21_size_t)strcspn(str1, str2);
  ck_assert_uint_eq(res_s21, res_std);
}
END_TEST

START_TEST(test_strcspn_empty_str1_empty_str2) {
  const char *str1 = "";
  const char *str2 = "";
  s21_size_t res_s21 = s21_strcspn(str1, str2);
  s21_size_t res_std = (s21_size_t)strcspn(str1, str2);
  ck_assert_uint_eq(res_s21, res_std);
}
END_TEST

START_TEST(test_strcspn_empty_str1) {
  const char *str1 = "";
  const char *str2 = "Hel";
  s21_size_t res_s21 = s21_strcspn(str1, str2);
  s21_size_t res_std = (s21_size_t)strcspn(str1, str2);
  ck_assert_uint_eq(res_s21, res_std);
}
END_TEST

START_TEST(test_strcspn_first_word_with_gap) {
  const char *str1 = "Yummy things";
  const char *str2 = "Yumth";
  s21_size_t res_s21 = s21_strcspn(str1, str2);
  s21_size_t res_std = (s21_size_t)strcspn(str1, str2);
  ck_assert_uint_eq(res_s21, res_std);
}
END_TEST

START_TEST(test_strcspn_whole_string_same_order) {
  const char *str1 = "Lorem ipsum";
  const char *str2 = "Lorem ipsum";
  s21_size_t res_s21 = s21_strcspn(str1, str2);
  s21_size_t res_std = (s21_size_t)strcspn(str1, str2);
  ck_assert_uint_eq(res_s21, res_std);
}
END_TEST

START_TEST(test_strcspn_whole_string_inverse_order) {
  const char *str1 = "Lorem ipsum";
  const char *str2 = "muspi meroL";
  s21_size_t res_s21 = s21_strcspn(str1, str2);
  s21_size_t res_std = (s21_size_t)strcspn(str1, str2);
  ck_assert_uint_eq(res_s21, res_std);
}
END_TEST

START_TEST(test_strcspn_whole_string_other_order) {
  const char *str1 = "Lorem ipsum";
  const char *str2 = "mLuersopi";
  s21_size_t res_s21 = s21_strcspn(str1, str2);
  s21_size_t res_std = (s21_size_t)strcspn(str1, str2);
  ck_assert_uint_eq(res_s21, res_std);
}
END_TEST

Suite *s21_strcspn_suite(void) {
  Suite *s = suite_create("s21_strcspn");
  TCase *tc_core = tcase_create("Core");
  tcase_add_test(tc_core, test_strcspn_single_in_the_beginning);
  tcase_add_test(tc_core, test_strcspn_single_in_the_middle);
  tcase_add_test(tc_core, test_strcspn_single_in_the_end);
  tcase_add_test(tc_core, test_strcspn_single_str2_multiple_in_the_middle);
  tcase_add_test(tc_core, test_strcspn_multiple_in_the_beginning);
  tcase_add_test(tc_core, test_strcspn_empty_str2);
  tcase_add_test(tc_core, test_strcspn_empty_str1_empty_str2);
  tcase_add_test(tc_core, test_strcspn_empty_str1);
  tcase_add_test(tc_core, test_strcspn_first_word_with_gap);
  tcase_add_test(tc_core, test_strcspn_whole_string_same_order);
  tcase_add_test(tc_core, test_strcspn_whole_string_inverse_order);
  tcase_add_test(tc_core, test_strcspn_whole_string_other_order);
  suite_add_tcase(s, tc_core);
  return s;
}
