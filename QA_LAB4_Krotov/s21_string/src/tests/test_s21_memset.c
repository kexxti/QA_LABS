#include "test_s21_memset.h"

#include "../string/s21_string.h"

START_TEST(test_memset_basic_char) {
  s21_size_t n = 50;
  char std_buf[50];
  char s21_buf[50];
  memset(std_buf, 'X', n);
  s21_memset(s21_buf, 'X', n);
  ck_assert_int_eq(memcmp(std_buf, s21_buf, n), 0);
}
END_TEST

START_TEST(test_memset_negative_c) {
  s21_size_t n = 50;
  char std_buf[50];
  char s21_buf[50];
  memset(std_buf, -1, n);
  s21_memset(s21_buf, -1, n);
  ck_assert_int_eq(memcmp(std_buf, s21_buf, sizeof(std_buf)), 0);
}
END_TEST

START_TEST(test_memset_int_array) {
  int std_arr[20];
  int s21_arr[20];
  size_t size = sizeof(std_arr);
  memset(std_arr, 1, size);
  s21_memset(s21_arr, 1, size);
  ck_assert_int_eq(memcmp(std_arr, s21_arr, size), 0);
}
END_TEST

START_TEST(test_memset_double_array) {
  double std_arr[10];
  double s21_arr[10];
  size_t size = sizeof(std_arr);
  memset(std_arr, 33, size);
  s21_memset(s21_arr, 33, size);
  ck_assert_int_eq(memcmp(std_arr, s21_arr, size), 0);
}
END_TEST

START_TEST(test_memset_partial) {
  char std_buf[100];
  char s21_buf[100];
  memset(std_buf, 55, sizeof(std_buf));
  memset(s21_buf, 55, sizeof(s21_buf));
  memset(std_buf, 'B', 50);
  s21_memset(s21_buf, 'B', 50);
  ck_assert_int_eq(memcmp(std_buf, s21_buf, sizeof(std_buf)), 0);
}
END_TEST

START_TEST(test_memset_dynamic_memory) {
  size_t size = 64;
  char *std_buf = malloc(size);
  char *s21_buf = malloc(size);
  ck_assert_ptr_nonnull(std_buf);
  ck_assert_ptr_nonnull(s21_buf);
  memset(std_buf, 'C', size);
  s21_memset(s21_buf, 'C', size);
  ck_assert_int_eq(memcmp(std_buf, s21_buf, size), 0);
  free(std_buf);
  free(s21_buf);
}
END_TEST

START_TEST(test_memset_large_buffer) {
  size_t size = 1024 * 1024;
  char *std_buf = malloc(size);
  char *s21_buf = malloc(size);
  ck_assert_ptr_nonnull(std_buf);
  ck_assert_ptr_nonnull(s21_buf);
  memset(std_buf, 'D', size);
  s21_memset(s21_buf, 'D', size);
  ck_assert_int_eq(memcmp(std_buf, s21_buf, size), 0);
  free(std_buf);
  free(s21_buf);
}
END_TEST

START_TEST(test_memset_unsigned_char) {
  unsigned char std_buf[20];
  unsigned char s21_buf[20];
  memset(std_buf, 0xAA, sizeof(std_buf));
  s21_memset(s21_buf, 0xAA, sizeof(s21_buf));
  ck_assert_int_eq(memcmp(std_buf, s21_buf, sizeof(std_buf)), 0);
}
END_TEST

START_TEST(test_return_value) {
  char buffer[100];
  void *ret_std = memset(buffer, 'E', sizeof(buffer));
  void *ret_s21 = s21_memset(buffer, 'E', sizeof(buffer));
  ck_assert_ptr_eq(ret_std, (void *)buffer);
  ck_assert_ptr_eq(ret_s21, (void *)buffer);
}
END_TEST

START_TEST(test_memset_partial_random) {
  char std_buf[100];
  char s21_buf[100];
  memset(std_buf, 0, sizeof(std_buf));
  s21_memset(s21_buf, 0, sizeof(s21_buf));
  int len = 37;
  memset(std_buf, 'Z', len);
  s21_memset(s21_buf, 'Z', len);
  ck_assert_int_eq(memcmp(std_buf, s21_buf, sizeof(std_buf)), 0);
}
END_TEST

Suite *s21_memset_suite(void) {
  Suite *s;
  TCase *tc_core;
  s = suite_create("s21_memset");
  tc_core = tcase_create("Core");
  tcase_add_test(tc_core, test_memset_basic_char);
  tcase_add_test(tc_core, test_memset_negative_c);
  tcase_add_test(tc_core, test_memset_int_array);
  tcase_add_test(tc_core, test_memset_double_array);
  tcase_add_test(tc_core, test_memset_partial);
  tcase_add_test(tc_core, test_memset_dynamic_memory);
  tcase_add_test(tc_core, test_memset_large_buffer);
  tcase_add_test(tc_core, test_memset_unsigned_char);
  tcase_add_test(tc_core, test_return_value);
  tcase_add_test(tc_core, test_memset_partial_random);
  suite_add_tcase(s, tc_core);
  return s;
}
