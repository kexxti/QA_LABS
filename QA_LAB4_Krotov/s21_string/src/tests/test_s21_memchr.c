#include "test_s21_memchr.h"

#include "../string/s21_string.h"

START_TEST(test_memchr_char_in_beginning_str) {
  TwoArrays arrays = init_struct_with_alphabet();
  s21_size_t n = 54;
  int c = 'A';
  char *res_s21 = s21_memchr(arrays.str, c, n);
  char *res_std = memchr(arrays.str, c, n);
  ck_assert_ptr_eq(res_s21, res_std);
}
END_TEST

START_TEST(test_memchr_zero_size) {
  TwoArrays arrays = init_struct_with_alphabet();
  s21_size_t n = 0;
  int c = 'A';
  char *res_s21 = s21_memchr(arrays.str, c, n);
  char *res_std = memchr(arrays.str, c, n);
  ck_assert_ptr_eq(res_s21, res_std);
}
END_TEST

START_TEST(test_memchr_char_in_end_of_src) {
  TwoArrays arrays = init_struct_with_alphabet();
  s21_size_t n = 54;
  int c = 'Z';
  char *res_s21 = s21_memchr(arrays.str, c, n);
  char *res_std = memchr(arrays.str, c, n);
  ck_assert_ptr_eq(res_s21, res_std);
}
END_TEST

START_TEST(test_memchr_char_in_end_of_src2) {
  TwoArrays arrays = init_struct_with_alphabet();
  s21_size_t n = 54;
  int c = 'z';
  char *res_s21 = s21_memchr(arrays.str, c, n);
  char *res_std = memchr(arrays.str, c, n);
  ck_assert_ptr_eq(res_s21, res_std);
}
END_TEST

START_TEST(test_memchr_char_in_middle_of_src) {
  TwoArrays arrays = init_struct_with_alphabet();
  s21_size_t n = 54;
  int c = 'M';
  char *res_s21 = s21_memchr(arrays.str, c, n);
  char *res_std = memchr(arrays.str, c, n);
  ck_assert_ptr_eq(res_s21, res_std);
}
END_TEST

START_TEST(test_memchr_char_in_middle_of_src2) {
  TwoArrays arrays = init_struct_with_alphabet();
  s21_size_t n = 54;
  int c = 'm';
  char *res_s21 = s21_memchr(arrays.str, c, n);
  char *res_std = memchr(arrays.str, c, n);
  ck_assert_ptr_eq(res_s21, res_std);
}
END_TEST

START_TEST(test_memchr_char_not_found) {
  TwoArrays arrays = init_struct_with_alphabet();
  s21_size_t n = 54;
  int c = '1';
  char *res_s21 = s21_memchr(arrays.str, c, n);
  char *res_std = memchr(arrays.str, c, n);
  ck_assert_ptr_eq(res_s21, res_std);
}
END_TEST

START_TEST(test_memchr_src_is_empty_string) {
  TwoArrays arrays = init_struct_with_alphabet();
  s21_size_t n = 54;
  int c = 'a';
  arrays.str[0] = '\0';
  char *res_s21 = s21_memchr(arrays.str, c, n);
  char *res_std = memchr(arrays.str, c, n);
  ck_assert_ptr_eq(res_s21, res_std);
}
END_TEST

START_TEST(test_memchr_char_samll_n) {
  TwoArrays arrays = init_struct_with_alphabet();
  s21_size_t n = 5;
  int c = 'C';
  char *res_s21 = s21_memchr(arrays.str, c, n);
  char *res_std = memchr(arrays.str, c, n);
  ck_assert_ptr_eq(res_s21, res_std);
}
END_TEST

START_TEST(test_memchr_char_samll_n_and_c_notfound) {
  TwoArrays arrays = init_struct_with_alphabet();
  s21_size_t n = 5;
  int c = 'a';
  char *res_s21 = s21_memchr(arrays.str, c, n);
  char *res_std = memchr(arrays.str, c, n);
  ck_assert_ptr_eq(res_s21, res_std);
}
END_TEST

Suite *s21_memchr_suite(void) {
  Suite *s = suite_create("s21_memchr");
  TCase *tc_core = tcase_create("Core");
  tcase_add_test(tc_core, test_memchr_char_in_beginning_str);
  tcase_add_test(tc_core, test_memchr_zero_size);
  tcase_add_test(tc_core, test_memchr_char_in_end_of_src);
  tcase_add_test(tc_core, test_memchr_char_in_end_of_src2);
  tcase_add_test(tc_core, test_memchr_char_in_middle_of_src);
  tcase_add_test(tc_core, test_memchr_char_in_middle_of_src2);
  tcase_add_test(tc_core, test_memchr_char_not_found);
  tcase_add_test(tc_core, test_memchr_src_is_empty_string);
  tcase_add_test(tc_core, test_memchr_char_samll_n);
  tcase_add_test(tc_core, test_memchr_char_samll_n_and_c_notfound);

  suite_add_tcase(s, tc_core);
  return s;
}

TwoArrays init_struct_with_alphabet(void) {
  TwoArrays arrays;
  for (int i = 0; i < 26; i++) {
    arrays.str[i] = (char)(65 + i);
  }
  arrays.str[26] = '\0';

  for (int i = 0; i < 26; i++) {
    arrays.str2[i] = (char)(97 + i);
  }
  arrays.str2[26] = '\0';
  return arrays;
}
