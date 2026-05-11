#include <stdbool.h>

#include "s21_string.h"

s21_size_t s21_strcspn(const char *str1, const char *str2) {
  s21_size_t len = 0;
  if (!str1 || !str2) return len;

  s21_size_t str2_len = s21_strlen(str2);
  bool continue_f = true;
  while (*str1 && continue_f) {
    for (s21_size_t i = 0; i < str2_len && continue_f; i++)
      if (*str1 == str2[i]) continue_f = false;
    if (continue_f) {
      str1++;
      len++;
    }
  }
  return len;
}