#include "s21_string.h"

char *s21_strncat(char *dest, const char *src, s21_size_t n) {
  char *dest_ptr = dest;
  while (*dest_ptr != '\0') {
    dest_ptr++;
  }
  s21_size_t i = 0;
  while (i < n && src[i] != '\0') {
    dest_ptr[i] = src[i];
    i++;
  }
  dest_ptr[i] = '\0';
  return dest;
}
