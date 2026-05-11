#include <check.h>
#include <stdio.h>
#include <stdlib.h>

#include "test_s21_insert.h"
#include "test_s21_memchr.h"
#include "test_s21_memcmp.h"
#include "test_s21_memcpy.h"
#include "test_s21_memset.h"
#include "test_s21_sprintf.h"
#include "test_s21_sscanf.h"
#include "test_s21_strchr.h"
#include "test_s21_strcspn.h"
#include "test_s21_strerror.h"
#include "test_s21_strlen.h"
#include "test_s21_strncat.h"
#include "test_s21_strncmp.h"
#include "test_s21_strncpy.h"
#include "test_s21_strpbrk.h"
#include "test_s21_strrchr.h"
#include "test_s21_strstr.h"
#include "test_s21_strtok.h"
#include "test_s21_to_lower.h"
#include "test_s21_to_upper.h"
#include "test_s21_trim.h"

int main() {
  int number_failed;
  SRunner *sr = srunner_create(s21_strncat_suite());
  srunner_add_suite(sr, s21_strchr_suite());
  srunner_add_suite(sr, s21_strrchr_suite());
  srunner_add_suite(sr, s21_strcspn_suite());
  srunner_add_suite(sr, s21_insert_suite());
  srunner_add_suite(sr, s21_strlen_suite());
  srunner_add_suite(sr, s21_strncpy_suite());
  srunner_add_suite(sr, s21_strstr_suite());
  srunner_add_suite(sr, s21_memchr_suite());
  srunner_add_suite(sr, s21_memcmp_suite());
  srunner_add_suite(sr, s21_memcpy_suite());
  srunner_add_suite(sr, s21_trim_suite());
  srunner_add_suite(sr, s21_to_lower_suite());
  srunner_add_suite(sr, s21_to_upper_suite());
  srunner_add_suite(sr, s21_memset_suite());
  srunner_add_suite(sr, s21_sscanf_suite());
  srunner_add_suite(sr, s21_strtok_suite());
  srunner_add_suite(sr, s21_strpbrk_suite());
  srunner_add_suite(sr, s21_strncmp_suite());
  srunner_add_suite(sr, s21_strerror_suite());
  srunner_add_suite(sr, s21_sprintf_suite());

  srunner_run_all(sr, CK_NORMAL);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return number_failed;
}
