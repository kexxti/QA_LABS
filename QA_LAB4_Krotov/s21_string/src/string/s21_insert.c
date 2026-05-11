#include <stdlib.h>

#include "s21_string.h"

void *s21_insert(const char *src, const char *str, s21_size_t start_index) {
  s21_size_t src_len = s21_strlen(src);
  if (!src || !str || start_index > src_len) return S21_NULL;
  s21_size_t str_len = s21_strlen(str);
  s21_size_t new_len = src_len + str_len;

  char *new_ptr = calloc(sizeof(char), new_len + 1);
  for (s21_size_t i = 0; i < start_index; i++) new_ptr[i] = src[i];
  for (s21_size_t i = 0; i < str_len; i++) new_ptr[i + start_index] = str[i];
  for (s21_size_t i = start_index + str_len; i < new_len; i++)
    new_ptr[i] = src[i - str_len];

  new_ptr[new_len] = '\0';
  return new_ptr;
}