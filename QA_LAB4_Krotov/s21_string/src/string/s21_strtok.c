#include "s21_string.h"

char *s21_strtok(char *str, const char *delim) {
  static char *olds = S21_NULL;
  if (!olds && !str) return S21_NULL;  // Если старой строки нет, выходим
  char *result = S21_NULL;

  if (str == S21_NULL) str = olds;
  str += s21_strspn(str, delim);
  if (*str != '\0') {
    char *end = str + s21_strcspn(str, delim);
    if (*end != '\0') {
      *end = '\0';
      olds = end + 1;
    } else {
      olds = S21_NULL;
    }
    result = str;
  } else {
    olds = S21_NULL;
  }
  return result;
}
