#include "test_s21_sprintf.h"

#include "../string/s21_string.h"

START_TEST(test_sprintf_basic_integers) {
  char buf1[256], buf2[256];
  int a = 42;
  int def = sprintf(buf1, "%d", a);
  int s21 = s21_sprintf(buf2, "%d", a);
  ck_assert_str_eq(buf1, buf2);
  ck_assert_int_eq(def, s21);
}
END_TEST

START_TEST(test_sprintf_negative_integers) {
  char buf1[256], buf2[256];
  int a = -42;
  int def = sprintf(buf1, "%d", a);
  int s21 = s21_sprintf(buf2, "%d", a);
  ck_assert_str_eq(buf1, buf2);
  ck_assert_int_eq(def, s21);
}
END_TEST

START_TEST(test_sprintf_width) {
  char buf1[256], buf2[256];
  int a = 123;
  int def = sprintf(buf1, "[%5d]", a);
  int s21 = s21_sprintf(buf2, "[%5d]", a);
  ck_assert_str_eq(buf1, buf2);
  ck_assert_int_eq(def, s21);
}
END_TEST

START_TEST(test_sprintf_precision_integer) {
  char buf1[256], buf2[256];
  int a = 123;
  int def = sprintf(buf1, "[%.5d]", a);
  int s21 = s21_sprintf(buf2, "[%.5d]", a);
  ck_assert_str_eq(buf1, buf2);
  ck_assert_int_eq(def, s21);
}
END_TEST

START_TEST(test_sprintf_left_align) {
  char buf1[256], buf2[256];
  int a = 123;
  int def = sprintf(buf1, "[%-5d]", a);
  int s21 = s21_sprintf(buf2, "[%-5d]", a);
  ck_assert_str_eq(buf1, buf2);
  ck_assert_int_eq(def, s21);
}
END_TEST

START_TEST(test_sprintf_zero_padding) {
  char buf1[256], buf2[256];
  int a = 123;
  int def = sprintf(buf1, "[%05d]", a);
  int s21 = s21_sprintf(buf2, "[%05d]", a);
  ck_assert_str_eq(buf1, buf2);
  ck_assert_int_eq(def, s21);
}
END_TEST

START_TEST(test_sprintf_plus_flag) {
  char buf1[256], buf2[256];
  int a = 123;
  int def = sprintf(buf1, "[%+d]", a);
  int s21 = s21_sprintf(buf2, "[%+d]", a);
  ck_assert_str_eq(buf1, buf2);
  ck_assert_int_eq(def, s21);
}
END_TEST

START_TEST(test_sprintf_space_flag) {
  char buf1[256], buf2[256];
  int a = 123;
  int def = sprintf(buf1, "[% d]", a);
  int s21 = s21_sprintf(buf2, "[% d]", a);
  ck_assert_str_eq(buf1, buf2);
  ck_assert_int_eq(def, s21);
}
END_TEST

START_TEST(test_sprintf_octal_alternative) {
  char buf1[256], buf2[256];
  unsigned int a = 123;
  int def = sprintf(buf1, "[%#o]", a);
  int s21 = s21_sprintf(buf2, "[%#o]", a);
  ck_assert_str_eq(buf1, buf2);
  ck_assert_int_eq(def, s21);
}
END_TEST

START_TEST(test_sprintf_hex_alternative_lower) {
  char buf1[256], buf2[256];
  unsigned int a = 0x1a3f;
  int def = sprintf(buf1, "[%#x]", a);
  int s21 = s21_sprintf(buf2, "[%#x]", a);
  ck_assert_str_eq(buf1, buf2);
  ck_assert_int_eq(def, s21);
}
END_TEST

START_TEST(test_sprintf_hex_alternative_upper) {
  char buf1[256], buf2[256];
  unsigned int a = 0x1a3f;
  int def = sprintf(buf1, "[%#X]", a);
  int s21 = s21_sprintf(buf2, "[%#X]", a);
  ck_assert_str_eq(buf1, buf2);
  ck_assert_int_eq(def, s21);
}
END_TEST

START_TEST(test_sprintf_char) {
  char buf1[256], buf2[256];
  char c = 'A';
  int def = sprintf(buf1, "[%c]", c);
  int s21 = s21_sprintf(buf2, "[%c]", c);
  ck_assert_str_eq(buf1, buf2);
  ck_assert_int_eq(def, s21);
}
END_TEST

START_TEST(test_sprintf_string) {
  char buf1[256], buf2[256];
  char *s = "Hello, world!";
  int def = sprintf(buf1, "[%s]", s);
  int s21 = s21_sprintf(buf2, "[%s]", s);
  ck_assert_str_eq(buf1, buf2);
  ck_assert_int_eq(def, s21);
}
END_TEST

START_TEST(test_sprintf_string_precision) {
  char buf1[256], buf2[256];
  char *s = "Hello, world!";
  int def = sprintf(buf1, "[%.5s]", s);
  int s21 = s21_sprintf(buf2, "[%.5s]", s);
  ck_assert_str_eq(buf1, buf2);
  ck_assert_int_eq(def, s21);
}
END_TEST

START_TEST(test_sprintf_pointer) {
  char buf1[256], buf2[256];
  void *p = (void *)0xDEADBEEF;
  int def = sprintf(buf1, "[%p]", p);
  int s21 = s21_sprintf(buf2, "[%p]", p);
  ck_assert_str_eq(buf1, buf2);
  ck_assert_int_eq(def, s21);
}
END_TEST

START_TEST(test_sprintf_percent) {
  char buf1[256], buf2[256];
  int def = sprintf(buf1, "100%% sure");
  int s21 = s21_sprintf(buf2, "100%% sure");
  ck_assert_str_eq(buf1, buf2);
  ck_assert_int_eq(def, s21);
}
END_TEST

START_TEST(test_sprintf_float) {
  char buf1[256], buf2[256];
  float f = 123.456f;
  int def = sprintf(buf1, "[%f]", f);
  int s21 = s21_sprintf(buf2, "[%f]", f);
  ck_assert_str_eq(buf1, buf2);
  ck_assert_int_eq(def, s21);
}
END_TEST

START_TEST(test_sprintf_float_precision) {
  char buf1[256], buf2[256];
  double d = 3.141592653589793;
  int def = sprintf(buf1, "[%.2f]", d);
  int s21 = s21_sprintf(buf2, "[%.2f]", d);
  ck_assert_str_eq(buf1, buf2);
  ck_assert_int_eq(def, s21);
}
END_TEST

START_TEST(test_sprintf_exponential) {
  char buf1[256], buf2[256];
  double d = 0.00012345;
  int def = sprintf(buf1, "[%e]", d);
  int s21 = s21_sprintf(buf2, "[%e]", d);
  ck_assert_str_eq(buf1, buf2);
  ck_assert_int_eq(def, s21);
}
END_TEST

START_TEST(test_sprintf_scientific_upper) {
  char buf1[256], buf2[256];
  double d = 123456.789;
  int def = sprintf(buf1, "[%E]", d);
  int s21 = s21_sprintf(buf2, "[%E]", d);
  ck_assert_str_eq(buf1, buf2);
  ck_assert_int_eq(def, s21);
}
END_TEST

START_TEST(test_sprintf_general) {
  char buf1[256], buf2[256];
  double d = 123.456;
  int def = sprintf(buf1, "[%g]", d);
  int s21 = s21_sprintf(buf2, "[%g]", d);
  ck_assert_str_eq(buf1, buf2);
  ck_assert_int_eq(def, s21);
}
END_TEST

START_TEST(test_sprintf_general_upper) {
  char buf1[256], buf2[256];
  double d = 123.456;
  int def = sprintf(buf1, "[%G]", d);
  int s21 = s21_sprintf(buf2, "[%G]", d);
  ck_assert_str_eq(buf1, buf2);
  ck_assert_int_eq(def, s21);
}
END_TEST

START_TEST(test_sprintf_dynamic_width_precision) {
  char buf1[256], buf2[256];
  int width = 10, prec = 4;
  double d = 3.141592653589793;
  int def = sprintf(buf1, "[%*.*f]", width, prec, d);
  int s21 = s21_sprintf(buf2, "[%*.*f]", width, prec, d);
  ck_assert_str_eq(buf1, buf2);
  ck_assert_int_eq(def, s21);
}
END_TEST

START_TEST(test_sprintf_multiple_specifiers) {
  char buf1[256], buf2[256];
  int a = -42;
  unsigned int u = 100;
  char c = 'Z';
  char *s = "Test";
  double d = 2.71828;
  int def = sprintf(
      buf1,
      "Int: [%d], Unsigned: [%u], Char: [%c], String: [%s], Float: [%.3f]", a,
      u, c, s, d);
  int s21 = s21_sprintf(
      buf2,
      "Int: [%d], Unsigned: [%u], Char: [%c], String: [%s], Float: [%.3f]", a,
      u, c, s, d);
  ck_assert_str_eq(buf1, buf2);
  ck_assert_int_eq(def, s21);
}
END_TEST

START_TEST(test_sprintf_empty_format) {
  char buf1[256], buf2[256];
  int def = sprintf(buf1, "%s", "");
  int s21 = s21_sprintf(buf2, "%s", "");
  ck_assert_str_eq(buf1, buf2);
  ck_assert_int_eq(def, s21);
}
END_TEST

START_TEST(test_sprintf_literal_only) {
  char buf1[256], buf2[256];
  int def = sprintf(buf1, "Just a literal string, no conversions.");
  int s21 = s21_sprintf(buf2, "Just a literal string, no conversions.");
  ck_assert_str_eq(buf1, buf2);
  ck_assert_int_eq(def, s21);
}
END_TEST

START_TEST(test_sprintf_null_string) {
  char buf1[256], buf2[256];
  char *null_str = NULL;
  int def = sprintf(buf1, "[%s]", null_str);
  int s21 = s21_sprintf(buf2, "[%s]", null_str);
  ck_assert_str_eq(buf1, buf2);
  ck_assert_int_eq(def, s21);
}
END_TEST

START_TEST(test_sprintf_float_alternative) {
  char buf1[256], buf2[256];
  double d = 12.0;
  int def = sprintf(buf1, "[%#.0f]", d);
  int s21 = s21_sprintf(buf2, "[%#.0f]", d);
  ck_assert_str_eq(buf1, buf2);
  ck_assert_int_eq(def, s21);
}
END_TEST

START_TEST(test_sprintf_number_read) {
  char str_def[256], str_s21[256];
  int value = 43;
  double d = 12.0;
  int num_s21, num_def;
  int def = sprintf(str_def, "[1234 %% %d%f%nh]", value, d, &num_def);
  int s21 = s21_sprintf(str_s21, "[1234 %% %d%f%nh]", value, d, &num_s21);
  ck_assert_str_eq(str_def, str_s21);
  ck_assert_int_eq(def, s21);
  ck_assert_int_eq(num_def, num_s21);
}
END_TEST

START_TEST(test_sprintf_length_modifiers) {
  char str_def[256], str_s21[256];
  short int short_value = 43;
  long int long_value = 4541651654894565;
  double d = 27.4 / 5.652137;
  long double l_d = 27.4 / 5.652137;
  int def = sprintf(str_def, "[1234 %%%ld %hd%lf%Lf]", long_value, short_value,
                    d, l_d);
  int s21 = s21_sprintf(str_s21, "[1234 %%%ld %hd%lf%Lf]", long_value,
                        short_value, d, l_d);
  ck_assert_str_eq(str_def, str_s21);
  ck_assert_int_eq(def, s21);
}
END_TEST

START_TEST(test_sprintf_length_modifiers_with_additional_flags) {
  char str_def[256], str_s21[256];
  short int short_value = 43;
  long int long_value = 4541651654894565;
  double d = 27.4 / 5.652137;
  long double l_d = 27.4 / 5.652137;
  int prec = 2;
  int prec_post = 4;
  int def = sprintf(str_def, "[1234 %%%-ld %3hd%*.*lf%#Lf]", long_value,
                    short_value, prec, prec_post, d, l_d);
  int s21 = s21_sprintf(str_s21, "[1234 %%%-ld %3hd%*.*lf%#Lf]", long_value,
                        short_value, prec, prec_post, d, l_d);
  ck_assert_str_eq(str_def, str_s21);
  ck_assert_int_eq(def, s21);
}
END_TEST

START_TEST(test_sprintf_space) {
  char str_def[256], str_s21[256];
  int value = 43;
  int def = sprintf(str_def, "[1234 %%%d\t%d\n%d %d\t \n\t%d     %d]", value,
                    value, value, value, value, value);
  int s21 = s21_sprintf(str_s21, "[1234 %%%d\t%d\n%d %d\t \n\t%d     %d]",
                        value, value, value, value, value, value);
  ck_assert_str_eq(str_def, str_s21);
  ck_assert_int_eq(def, s21);
}
END_TEST

START_TEST(test_sprintf_signed_float) {
  char buf1[256], buf2[256];
  float a = -4123.4;
  float b = 7.15;
  int def = sprintf(buf1, "[%+f %+f %f %f]", a, b, a, b);
  int s21 = s21_sprintf(buf2, "[%+f %+f %f %f]", a, b, a, b);
  ck_assert_str_eq(buf1, buf2);
  ck_assert_int_eq(def, s21);
}
END_TEST

START_TEST(test_sprintf_float_precision_1) {
  char buf1[256], buf2[256];
  float a = -4123.4;
  float b = 7.15;
  int def = sprintf(buf1, "[%+.1f %+.1f %1.f %1.f]", a, b, a, b);
  int s21 = s21_sprintf(buf2, "[%+.1f %+.1f %1.f %1.f]", a, b, a, b);
  ck_assert_str_eq(buf1, buf2);
  ck_assert_int_eq(def, s21);
}
END_TEST

START_TEST(test_sprintf_negative_double_sci) {
  char buf1[256], buf2[256];
  double a = -4123.4;
  int def = sprintf(buf1, "[%g %G %e %E %f]", a, a, a, a, a);
  int s21 = s21_sprintf(buf2, "[%g %G %e %E %f]", a, a, a, a, a);
  ck_assert_str_eq(buf1, buf2);
  ck_assert_int_eq(def, s21);
}
END_TEST

START_TEST(test_sprintf_negative_int) {
  char buf1[256], buf2[256];
  int a = -4123;
  int def = sprintf(buf1, "[%d %i %x %u %o]", a, a, a, a, a);
  int s21 = s21_sprintf(buf2, "[%d %i %x %u %o]", a, a, a, a, a);
  ck_assert_str_eq(buf1, buf2);
  ck_assert_int_eq(def, s21);
}
END_TEST

Suite *s21_sprintf_suite(void) {
  Suite *s = suite_create("s21_sprintf");
  TCase *tc = tcase_create("Core");

  tcase_add_test(tc, test_sprintf_basic_integers);
  tcase_add_test(tc, test_sprintf_negative_integers);
  tcase_add_test(tc, test_sprintf_width);
  tcase_add_test(tc, test_sprintf_precision_integer);
  tcase_add_test(tc, test_sprintf_left_align);
  tcase_add_test(tc, test_sprintf_zero_padding);
  tcase_add_test(tc, test_sprintf_plus_flag);
  tcase_add_test(tc, test_sprintf_space_flag);
  tcase_add_test(tc, test_sprintf_octal_alternative);
  tcase_add_test(tc, test_sprintf_hex_alternative_lower);
  tcase_add_test(tc, test_sprintf_hex_alternative_upper);
  tcase_add_test(tc, test_sprintf_char);
  tcase_add_test(tc, test_sprintf_string);
  tcase_add_test(tc, test_sprintf_string_precision);
  tcase_add_test(tc, test_sprintf_pointer);
  tcase_add_test(tc, test_sprintf_percent);
  tcase_add_test(tc, test_sprintf_float);
  tcase_add_test(tc, test_sprintf_float_precision);
  tcase_add_test(tc, test_sprintf_exponential);
  tcase_add_test(tc, test_sprintf_scientific_upper);
  tcase_add_test(tc, test_sprintf_general);
  tcase_add_test(tc, test_sprintf_general_upper);
  tcase_add_test(tc, test_sprintf_dynamic_width_precision);
  tcase_add_test(tc, test_sprintf_multiple_specifiers);
  tcase_add_test(tc, test_sprintf_empty_format);
  tcase_add_test(tc, test_sprintf_literal_only);
  tcase_add_test(tc, test_sprintf_null_string);
  tcase_add_test(tc, test_sprintf_float_alternative);
  tcase_add_test(tc, test_sprintf_number_read);
  tcase_add_test(tc, test_sprintf_length_modifiers);
  tcase_add_test(tc, test_sprintf_length_modifiers_with_additional_flags);
  tcase_add_test(tc, test_sprintf_space);
  tcase_add_test(tc, test_sprintf_signed_float);
  tcase_add_test(tc, test_sprintf_float_precision_1);
  tcase_add_test(tc, test_sprintf_negative_double_sci);
  tcase_add_test(tc, test_sprintf_negative_int);

  suite_add_tcase(s, tc);
  return s;
}
