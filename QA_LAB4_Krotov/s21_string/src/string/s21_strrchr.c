#include "s21_string.h"

char *s21_strrchr(const char *str, int c) {
  char *result = S21_NULL;
  if (!str) return result;

  s21_size_t str_len = s21_strlen(str);
  for (s21_size_t i = str_len; i > 0 && !result; i--) {
    if (str[i - 1] == c) result = (void *)str + (i - 1);
  }
  if (str[0] == c && !result) result = (void *)str;
  if (result == S21_NULL && c == '\0') result = (void *)str + str_len;

  return result;
}
