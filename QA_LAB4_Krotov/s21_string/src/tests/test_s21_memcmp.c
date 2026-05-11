#include "test_s21_memcmp.h"

#include "../string/s21_string.h"

START_TEST(test_memcmp_equal_string) {
  char str1[100];
  char str2[100];
  strcpy(str1, "123456");
  strcpy(str2, "123456");
  s21_size_t n = 6;
  int std = 0;
  int s21 = 0;
  if (memcmp(str1, str2, n) > 0) std = 1;
  if (memcmp(str1, str2, n) < 0) std = -1;
  if (s21_memcmp(str1, str2, n) > 0) s21 = 1;
  if (s21_memcmp(str1, str2, n) < 0) s21 = -1;
  ck_assert_int_eq(std, s21);
}
END_TEST

START_TEST(test_memcmp_NULL_zero_length) {
  char *str1 = NULL;
  char *str2 = NULL;
  s21_size_t n = 0;
  int std = 0;
  int s21 = 0;
  if (memcmp(str1, str2, n) > 0) std = 1;
  if (memcmp(str1, str2, n) < 0) std = -1;
  if (s21_memcmp(str1, str2, n) > 0) s21 = 1;
  if (s21_memcmp(str1, str2, n) < 0) s21 = -1;
  ck_assert_int_eq(std, s21);
}
END_TEST

START_TEST(test_memcmp_diff_beginning) {
  char str1[] = "ABCDEF";
  char str2[] = "XBCDEF";
  s21_size_t n = 6;
  int std = 0;
  int s21 = 0;
  if (memcmp(str1, str2, n) > 0) std = 1;
  if (memcmp(str1, str2, n) < 0) std = -1;
  if (s21_memcmp(str1, str2, n) > 0) s21 = 1;
  if (s21_memcmp(str1, str2, n) < 0) s21 = -1;
  ck_assert_int_eq(std, s21);
}
END_TEST

START_TEST(test_memcmp_diff_middle) {
  char str1[] = "ABCDEFGH";
  char str2[] = "ABCDZFGH";
  s21_size_t n = 8;
  int std = 0;
  int s21 = 0;
  if (memcmp(str1, str2, n) > 0) std = 1;
  if (memcmp(str1, str2, n) < 0) std = -1;
  if (s21_memcmp(str1, str2, n) > 0) s21 = 1;
  if (s21_memcmp(str1, str2, n) < 0) s21 = -1;
  ck_assert_int_eq(std, s21);
}
END_TEST

START_TEST(test_memcmp_diff_end) {
  char str1[] = "ABCDEf";
  char str2[] = "ABCDEg";
  s21_size_t n = 6;
  int std = 0;
  int s21 = 0;
  if (memcmp(str1, str2, n) > 0) std = 1;
  if (memcmp(str1, str2, n) < 0) std = -1;
  if (s21_memcmp(str1, str2, n) > 0) s21 = 1;
  if (s21_memcmp(str1, str2, n) < 0) s21 = -1;
  ck_assert_int_eq(std, s21);
}
END_TEST

START_TEST(test_memcmp_zero_length) {
  char str1[] = "Hello";
  char str2[] = "World";
  s21_size_t n = 0;
  int std = 0;
  int s21 = 0;
  if (memcmp(str1, str2, n) > 0) std = 1;
  if (memcmp(str1, str2, n) < 0) std = -1;
  if (s21_memcmp(str1, str2, n) > 0) s21 = 1;
  if (s21_memcmp(str1, str2, n) < 0) s21 = -1;
  ck_assert_int_eq(std, s21);
}
END_TEST

START_TEST(test_memcmp_binary) {
  unsigned char str1[] = {0x00, 0x01, 0x02, 0xFF, 0x10, 0x11};
  unsigned char str2[] = {0x00, 0x01, 0x02, 0xF0, 0x10, 0x11};
  s21_size_t n = 6;
  int std = 0;
  int s21 = 0;
  if (memcmp(str1, str2, n) > 0) std = 1;
  if (memcmp(str1, str2, n) < 0) std = -1;
  if (s21_memcmp(str1, str2, n) > 0) s21 = 1;
  if (s21_memcmp(str1, str2, n) < 0) s21 = -1;
  ck_assert_int_eq(std, s21);
}
END_TEST

START_TEST(test_memcmp_equal_binary) {
  unsigned char str1[] = {0x00, 0x01, 0x02, 0xFF, 0x10, 0x11};
  unsigned char str2[] = {0x00, 0x01, 0x02, 0xFF, 0x10, 0x11};
  s21_size_t n = 6;
  int std = 0;
  int s21 = 0;
  if (memcmp(str1, str2, n) > 0) std = 1;
  if (memcmp(str1, str2, n) < 0) std = -1;
  if (s21_memcmp(str1, str2, n) > 0) s21 = 1;
  if (s21_memcmp(str1, str2, n) < 0) s21 = -1;
  ck_assert_int_eq(std, s21);
}
END_TEST

START_TEST(test_memcmp_equal_long_array) {
  int str1[1001];
  int str2[1001];
  for (int i = 0; i < 1001; i++) {
    str1[i] = i;
    str2[i] = i;
  }
  s21_size_t n = 1000;
  int std = 0;
  int s21 = 0;
  if (memcmp(str1, str2, n) > 0) std = 1;
  if (memcmp(str1, str2, n) < 0) std = -1;
  if (s21_memcmp(str1, str2, n) > 0) s21 = 1;
  if (s21_memcmp(str1, str2, n) < 0) s21 = -1;
  ck_assert_int_eq(std, s21);
}
END_TEST

START_TEST(test_memcmp_long_array) {
  int str1[1001];
  int str2[1001];
  for (int i = 0; i < 1001; i++) {
    str1[i] = i;
    str2[i] = i;
  }
  str1[555] = 99999;
  s21_size_t n = 1000;
  int std = 0;
  int s21 = 0;
  if (memcmp(str1, str2, n) > 0) std = 1;
  if (memcmp(str1, str2, n) < 0) std = -1;
  if (s21_memcmp(str1, str2, n) > 0) s21 = 1;
  if (s21_memcmp(str1, str2, n) < 0) s21 = -1;
  ck_assert_int_eq(std, s21);
}
END_TEST

Suite *s21_memcmp_suite(void) {
  Suite *s = suite_create("s21_memcmp");
  TCase *tc_core = tcase_create("Core");
  tcase_add_test(tc_core, test_memcmp_equal_string);
  tcase_add_test(tc_core, test_memcmp_NULL_zero_length);
  tcase_add_test(tc_core, test_memcmp_diff_beginning);
  tcase_add_test(tc_core, test_memcmp_diff_middle);
  tcase_add_test(tc_core, test_memcmp_diff_end);
  tcase_add_test(tc_core, test_memcmp_zero_length);
  tcase_add_test(tc_core, test_memcmp_binary);
  tcase_add_test(tc_core, test_memcmp_equal_binary);
  tcase_add_test(tc_core, test_memcmp_equal_long_array);
  tcase_add_test(tc_core, test_memcmp_long_array);

  suite_add_tcase(s, tc_core);
  return s;
}
