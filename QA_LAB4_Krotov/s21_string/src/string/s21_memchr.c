#include "s21_string.h"

void *s21_memchr(const void *str, int c, s21_size_t n) {
  s21_size_t i = 0;
  unsigned char *mem = (unsigned char *)str;
  void *result = S21_NULL;
  for (i = 0; i < n; i++) {
    if (mem[i] == (unsigned char)c) {
      result = mem + i;
      break;
    }
  }
  return result;
}
