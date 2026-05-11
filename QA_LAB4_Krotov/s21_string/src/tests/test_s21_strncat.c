#include "test_s21_strncat.h"

#include "../string/s21_string.h"

START_TEST(test_strncat_zero_n) {
  char dest_s21[100];
  char dest_std[100];
  const char *src;
  const char initial_dest[] = "Hello";
  const char src_str[] = "World";
  reset_buffers(dest_s21, dest_std, initial_dest, &src, src_str);
  s21_strncat(dest_s21, src, 0);
  strncat(dest_std, src, 0);
  ck_assert_str_eq(dest_s21, dest_std);
}
END_TEST

START_TEST(test_strncat_src_shorter_than_n) {
  char dest_s21[100];
  char dest_std[100];
  const char *src;
  const char initial_dest[] = "Hello, ";
  const char src_str[] = "Check";
  s21_size_t n = 50;
  reset_buffers(dest_s21, dest_std, initial_dest, &src, src_str);
  s21_strncat(dest_s21, src, n);
  strncat(dest_std, src, n);
  ck_assert_str_eq(dest_s21, dest_std);
}
END_TEST

START_TEST(test_strncat_src_longer_than_n) {
  char dest_s21[100];
  char dest_std[100];
  const char *src;
  const char initial_dest[] = "Hello, ";
  const char src_str[] = "Check World";
  s21_size_t n = 5;
  reset_buffers(dest_s21, dest_std, initial_dest, &src, src_str);
  s21_strncat(dest_s21, src, n);
  strncat(dest_std, src, n);
  ck_assert_str_eq(dest_s21, dest_std);
}
END_TEST

START_TEST(test_strncat_empty_dest) {
  char dest_s21[100];
  char dest_std[100];
  const char *src;
  const char initial_dest[] = "";
  const char src_str[] = "Non-empty";
  s21_size_t n = 4;
  reset_buffers(dest_s21, dest_std, initial_dest, &src, src_str);
  s21_strncat(dest_s21, src, n);
  strncat(dest_std, src, n);
  ck_assert_str_eq(dest_s21, dest_std);
}
END_TEST

START_TEST(test_strncat_empty_src) {
  char dest_s21[100];
  char dest_std[100];
  const char *src;
  const char initial_dest[] = "Hello world";
  const char src_str[] = "";
  s21_size_t n = 5;
  reset_buffers(dest_s21, dest_std, initial_dest, &src, src_str);
  s21_strncat(dest_s21, src, n);
  strncat(dest_std, src, n);
  ck_assert_str_eq(dest_s21, dest_std);
}
END_TEST

START_TEST(test_strncat_extended_ascii) {
  char dest_s21[100];
  char dest_std[100];
  const char *src;
  const char initial_dest[] = "Я пошел в школу 21";
  const char src_str[] = ", потому что я хочу научиться";
  s21_size_t n = 19;
  reset_buffers(dest_s21, dest_std, initial_dest, &src, src_str);
  s21_strncat(dest_s21, src, n);
  strncat(dest_std, src, n);
  ck_assert_str_eq(dest_s21, dest_std);
}
END_TEST

Suite *s21_strncat_suite(void) {
  Suite *s = suite_create("s21_strncat");
  TCase *tc_core = tcase_create("Core");
  tcase_add_test(tc_core, test_strncat_zero_n);
  tcase_add_test(tc_core, test_strncat_src_shorter_than_n);
  tcase_add_test(tc_core, test_strncat_src_longer_than_n);
  tcase_add_test(tc_core, test_strncat_empty_dest);
  tcase_add_test(tc_core, test_strncat_empty_src);
  tcase_add_test(tc_core, test_strncat_extended_ascii);
  suite_add_tcase(s, tc_core);
  return s;
}

void reset_buffers(char *dest_s21, char *dest_std, const char *initial_dest,
                   const char **src_ptr, const char *src_str) {
  strcpy(dest_s21, initial_dest);
  strcpy(dest_std, initial_dest);
  *src_ptr = src_str;
}
