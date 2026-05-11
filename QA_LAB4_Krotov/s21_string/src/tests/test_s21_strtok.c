#include "test_s21_strtok.h"

START_TEST(test_basic_delim) {
  char str1[] = "Hello, World!";
  char str1_copy[] = "Hello, World!";
  const char *delim = ",";
  char *res_s21 = s21_strtok(str1_copy, delim);
  char *res_std = strtok(str1, delim);
  while (res_std != NULL && res_s21 != NULL) {
    ck_assert_str_eq(res_s21, res_std);
    res_s21 = s21_strtok(NULL, delim);
    res_std = strtok(NULL, delim);
  }
  ck_assert_ptr_eq(res_s21, res_std);
}
END_TEST

START_TEST(test_wrong_delim) {
  char str1[] = "Hello, World!";
  char str1_copy[] = "Hello, World!";
  const char *delim = "123";
  char *res_s21 = s21_strtok(str1_copy, delim);
  char *res_std = strtok(str1, delim);
  while (res_std != NULL && res_s21 != NULL) {
    ck_assert_str_eq(res_s21, res_std);
    res_s21 = s21_strtok(NULL, delim);
    res_std = strtok(NULL, delim);
  }
  ck_assert_ptr_eq(res_s21, res_std);
}
END_TEST

START_TEST(test_leading_delim) {
  char str1[] = ",Hello,World!";
  char str1_copy[] = ",Hello,World!";
  const char *delim = ",";
  char *res_s21 = s21_strtok(str1_copy, delim);
  char *res_std = strtok(str1, delim);
  while (res_std != NULL && res_s21 != NULL) {
    ck_assert_str_eq(res_s21, res_std);
    res_s21 = s21_strtok(NULL, delim);
    res_std = strtok(NULL, delim);
  }
  ck_assert_ptr_eq(res_s21, res_std);
}
END_TEST

START_TEST(test_complex_delim) {
  char str1[] = "H,-|-|-,ello, Wor,-|-|-,ld!";
  char str1_copy[] = "H,-|-|-,ello, Wor,-|-|-,ld!";
  const char *delim = ",-|-|-,";
  char *res_s21 = s21_strtok(str1_copy, delim);
  char *res_std = strtok(str1, delim);
  while (res_std != NULL && res_s21 != NULL) {
    ck_assert_str_eq(res_s21, res_std);
    res_s21 = s21_strtok(NULL, delim);
    res_std = strtok(NULL, delim);
  }
  ck_assert_ptr_eq(res_s21, res_std);
}
END_TEST

START_TEST(test_empty_str) {
  char str1[] = "";
  char str1_copy[] = "";
  const char *delim = ",-|-|-";
  char *res_s21 = s21_strtok(str1_copy, delim);
  char *res_std = strtok(str1, delim);
  ck_assert_ptr_eq(res_s21, res_std);
}
END_TEST

START_TEST(test_multiple_calls) {
  char str1[] = "one,two,three";
  char str1_copy[] = "one,two,three";
  const char *delim = ",";
  char *res_s21 = s21_strtok(str1_copy, delim);
  char *res_std = strtok(str1, delim);

  while (res_std != NULL && res_s21 != NULL) {
    ck_assert_str_eq(res_s21, res_std);
    res_s21 = s21_strtok(NULL, delim);
    res_std = strtok(NULL, delim);
  }

  ck_assert_ptr_eq(res_s21, res_std);
}
END_TEST

START_TEST(test_trailing_delim) {
  char str1[] = "Hello,World!,";
  char str1_copy[] = "Hello,World!,";
  const char *delim = ",";
  char *res_s21 = s21_strtok(str1_copy, delim);
  char *res_std = strtok(str1, delim);
  while (res_std != NULL && res_s21 != NULL) {
    ck_assert_str_eq(res_s21, res_std);
    res_s21 = s21_strtok(NULL, delim);
    res_std = strtok(NULL, delim);
  }
  ck_assert_ptr_eq(res_s21, res_std);
}
END_TEST

START_TEST(test_only_delim) {
  char str1[] = ",,,,";
  char str1_copy[] = ",,,,";
  const char *delim = ",";
  char *res_s21 = s21_strtok(str1_copy, delim);
  char *res_std = strtok(str1, delim);
  ck_assert_ptr_eq(res_s21, res_std);
}
END_TEST

START_TEST(test_long_string) {
  char str1[] = "one,two;three|four five.six";
  char str1_copy[] = "one,two;three|four five.six";
  const char *delim = ",;| .";
  char *res_s21 = s21_strtok(str1_copy, delim);
  char *res_std = strtok(str1, delim);
  while (res_std != NULL && res_s21 != NULL) {
    ck_assert_str_eq(res_s21, res_std);
    res_s21 = s21_strtok(NULL, delim);
    res_std = strtok(NULL, delim);
  }
  ck_assert_ptr_eq(res_s21, res_std);
}
END_TEST

Suite *s21_strtok_suite(void) {
  Suite *s = suite_create("s21_strtok");
  TCase *tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_basic_delim);
  tcase_add_test(tc_core, test_wrong_delim);
  tcase_add_test(tc_core, test_complex_delim);
  tcase_add_test(tc_core, test_empty_str);
  tcase_add_test(tc_core, test_multiple_calls);
  tcase_add_test(tc_core, test_leading_delim);
  tcase_add_test(tc_core, test_trailing_delim);
  tcase_add_test(tc_core, test_only_delim);
  tcase_add_test(tc_core, test_long_string);

  suite_add_tcase(s, tc_core);
  return s;
}
