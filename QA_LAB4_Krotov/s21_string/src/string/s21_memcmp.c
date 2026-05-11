#include "s21_string.h"

int s21_memcmp(const void *str1, const void *str2, s21_size_t n) {
  int result = 0;
  unsigned char *line1 = (unsigned char *)str1;
  unsigned char *line2 = (unsigned char *)str2;
  if (n > 0) {
    for (s21_size_t i = 0; i < n; i++) {
      if (line1[i] != line2[i]) {
        result = line1[i] - line2[i];
        break;
      }
    }
  }
  return result;
}
