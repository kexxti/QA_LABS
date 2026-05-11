#include "s21_string.h"

s21_size_t s21_strrspn(const char *str1, const char *str2) {
  s21_size_t count = 0;
  const char *end = str1 + s21_strlen(str1);

  while (end > str1) {
    end--;
    if (!s21_strchr(str2, *end)) {
      break;
    }
    count++;
  }
  return count;
}
