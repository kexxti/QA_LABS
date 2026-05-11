
#include "test_s21_strlen.h"

START_TEST(test_strlen_empty_string) {
  char s21_str[] = "";
  char std_str[] = "";
  ck_assert_int_eq(s21_strlen(s21_str), strlen(std_str));
}
END_TEST

START_TEST(test_strlen_usual_string) {
  char s21_str[] = "Hello";
  char std_str[] = "Hello";
  ck_assert_int_eq(s21_strlen(s21_str), strlen(std_str));
}
END_TEST

START_TEST(test_strlen_with_spaces) {
  char s21_str[] = "\tHello world!\n";
  char std_str[] = "\tHello world!\n";
  ck_assert_int_eq(s21_strlen(s21_str), strlen(std_str));
}
END_TEST

START_TEST(test_strlen_rus) {
  char s21_str[] = "Я пошел в школу 21";
  char std_str[] = "Я пошел в школу 21";
  ck_assert_int_eq(s21_strlen(s21_str), strlen(std_str));
}
END_TEST

START_TEST(test_strlen_long_string) {
  char s21_str[] =
      "For almost a year, a group of the brightest mathematicians, linguists, "
      "and crossword puzzle enthusiasts had been trying to solve the most "
      "difficult problem of all: breaking the German Enigma cipher, whose "
      "codes changed daily and whose number of possible combinations was about "
      "two to the power of 64. "
      "The group often had to come up with different algorithms, and they even "
      "developed a special set of keywords and their syntax for easy "
      "communication and logging, which is exactly like the well-known C "
      "language in our universe.";
  char std_str[] =
      "For almost a year, a group of the brightest mathematicians, linguists, "
      "and crossword puzzle enthusiasts had been trying to solve the most "
      "difficult problem of all: breaking the German Enigma cipher, whose "
      "codes changed daily and whose number of possible combinations was about "
      "two to the power of 64. "
      "The group often had to come up with different algorithms, and they even "
      "developed a special set of keywords and their syntax for easy "
      "communication and logging, which is exactly like the well-known C "
      "language in our universe.";
  ck_assert_int_eq(s21_strlen(s21_str), strlen(std_str));
}
END_TEST

Suite *s21_strlen_suite(void) {
  Suite *s = suite_create("s21_strlen");
  TCase *tc_core = tcase_create("Core");
  tcase_add_test(tc_core, test_strlen_empty_string);
  tcase_add_test(tc_core, test_strlen_usual_string);
  tcase_add_test(tc_core, test_strlen_with_spaces);
  tcase_add_test(tc_core, test_strlen_rus);
  tcase_add_test(tc_core, test_strlen_long_string);
  suite_add_tcase(s, tc_core);
  return s;
}
