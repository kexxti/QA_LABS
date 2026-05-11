#include "s21_string.h"

char *s21_strchr(const char *str, int c) {
  char *result = S21_NULL;
  char ch = c;
  while (*str != '\0') {
    if (*str == ch) {
      result = (char *)str;
      break;
    }
    str++;
  }
  if (result == S21_NULL && ch == '\0') {
    result = (char *)str;
  }
  return result;
}
