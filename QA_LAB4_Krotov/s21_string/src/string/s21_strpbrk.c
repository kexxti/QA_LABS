#include "s21_string.h"

char *s21_strpbrk(const char *str1, const char *str2) {
  str1 += s21_strcspn(str1, str2);
  return *str1 ? (char *)str1 : S21_NULL;
}
