#include "test_s21_strerror.h"

#include "../string/s21_strerror.h"
#include "../string/s21_string.h"

START_TEST(test_strerror_OOB_codes) {
  for (int errn = -5; errn < 0; errn++) {
    char *def_res, *s21_res;
    def_res = strerror(errn);
    s21_res = s21_strerror(errn);
    ck_assert_pstr_eq(def_res, s21_res);
  }
  s21_size_t errors_sz = sizeof(S21_ERRORS) / sizeof(S21_ERRORS[0]);
  for (s21_size_t errn = errors_sz; errn < errors_sz * 1.2; errn++) {
    char *def_res, *s21_res;
    def_res = strerror(errn);
    s21_res = s21_strerror(errn);
    ck_assert_pstr_eq(def_res, s21_res);
  }
}
END_TEST

START_TEST(test_strerror_normal_codes) {
  s21_size_t errors_sz = sizeof(S21_ERRORS) / sizeof(S21_ERRORS[0]);
  for (s21_size_t errn = 0; errn < errors_sz; errn++) {
    char *def_res, *s21_res;
    def_res = strerror(errn);
    s21_res = s21_strerror(errn);
    ck_assert_pstr_eq(def_res, s21_res);
  }
}
END_TEST

Suite *s21_strerror_suite(void) {
  Suite *s = suite_create("s21_strerror");
  TCase *tc = tcase_create("All testes");
  tcase_add_test(tc, test_strerror_OOB_codes);
  tcase_add_test(tc, test_strerror_normal_codes);
  suite_add_tcase(s, tc);
  return s;
}