#include "test_s21_memcpy.h"

#include "../string/s21_string.h"

START_TEST(test_memcpy_basic) {
  char src[] = "Hello, World!";
  char dest[50] = {0};
  s21_size_t n = 10;
  char *res_s21 = s21_memcpy(dest, src, n);
  char *res_std = memcpy(dest, src, n);
  ck_assert_str_eq(res_s21, res_std);
  ck_assert_ptr_eq(res_s21, res_std);
}
END_TEST

START_TEST(test_memcpy_zero_length) {
  char src[] = "test";
  char dest[50] = "XXXXXXXXXX";
  size_t n = 0;
  char *res_s21 = s21_memcpy(dest, src, n);
  char *res_std = memcpy(dest, src, n);
  ck_assert_str_eq(res_s21, res_std);
  ck_assert_ptr_eq(res_s21, res_std);
  ck_assert_str_eq(res_s21, dest);
  ck_assert_ptr_eq(dest, res_std);
}
END_TEST

START_TEST(test_memcpy_binary) {
  unsigned char src[5] = {0x00, 0xFF, 0xAB, 0x12, 0x34};
  unsigned char dest[5] = {0};
  size_t n = 5;
  char *res_s21 = s21_memcpy(dest, src, n);
  char *res_std = memcpy(dest, src, n);
  ck_assert_ptr_eq(res_s21, res_std);
  ck_assert_int_eq(memcmp(res_s21, res_std, n), 0);
}
END_TEST

Suite *s21_memcpy_suite(void) {
  Suite *s = suite_create("s21_memcpy");
  TCase *tc_core = tcase_create("Core");
  tcase_add_test(tc_core, test_memcpy_basic);
  tcase_add_test(tc_core, test_memcpy_zero_length);
  tcase_add_test(tc_core, test_memcpy_binary);

  suite_add_tcase(s, tc_core);
  return s;
}
