#include "test_s21_to_lower.h"

START_TEST(test_to_lower_empty) {
  const char *str = "";
  char *res_s21 = s21_to_lower(str);
  const char *res_std = "";
  ck_assert_str_eq(res_s21, res_std);
  if (res_s21) free(res_s21);
}
END_TEST

START_TEST(test_to_lower_all_capital) {
  const char *str = "HELLO, WORLD!";
  char *res_s21 = s21_to_lower(str);
  const char *res_std = "hello, world!";
  ck_assert_str_eq(res_s21, res_std);
  if (res_s21) free(res_s21);
}
END_TEST

START_TEST(test_to_lower_all_lower) {
  const char *str = "hello, world!";
  char *res_s21 = s21_to_lower(str);
  const char *res_std = "hello, world!";
  ck_assert_str_eq(res_s21, res_std);
  if (res_s21) free(res_s21);
}
END_TEST

START_TEST(test_to_lower_mixed) {
  const char *str = "HeLLo, WoRLd!";
  char *res_s21 = s21_to_lower(str);
  const char *res_std = "hello, world!";
  ck_assert_str_eq(res_s21, res_std);
  if (res_s21) free(res_s21);
}
END_TEST

START_TEST(test_to_lower_null) {
  const char *str = S21_NULL;
  char *res_s21 = s21_to_lower(str);
  ck_assert_ptr_null(res_s21);
}
END_TEST

START_TEST(test_to_lower_special_chars) {
  const char *str = "1234567890!@#$%^&*()_+";
  char *res_s21 = s21_to_lower(str);
  const char *res_std = "1234567890!@#$%^&*()_+";
  ck_assert_str_eq(res_s21, res_std);
  if (res_s21) free(res_s21);
}
END_TEST

START_TEST(test_to_lower_with_spaces) {
  const char *str = "  HELLO,   WORLD!   ";
  char *res_s21 = s21_to_lower(str);
  const char *res_std = "  hello,   world!   ";
  ck_assert_str_eq(res_s21, res_std);
  if (res_s21) free(res_s21);
}
END_TEST

Suite *s21_to_lower_suite(void) {
  Suite *s = suite_create("s21_to_lower");
  TCase *tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_to_lower_empty);
  tcase_add_test(tc_core, test_to_lower_all_capital);
  tcase_add_test(tc_core, test_to_lower_all_lower);
  tcase_add_test(tc_core, test_to_lower_mixed);
  tcase_add_test(tc_core, test_to_lower_null);
  tcase_add_test(tc_core, test_to_lower_special_chars);
  tcase_add_test(tc_core, test_to_lower_with_spaces);

  suite_add_tcase(s, tc_core);
  return s;
}
