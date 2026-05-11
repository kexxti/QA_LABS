#include "s21_string.h"

void *s21_memcpy(void *dest, const void *src, s21_size_t n) {
  unsigned char *result = (unsigned char *)dest;
  unsigned char *str2 = (unsigned char *)src;
  if (n != 0) {
    for (s21_size_t i = 0; i < n; i++) {
      result[i] = str2[i];
    }
  }
  return result;
}
