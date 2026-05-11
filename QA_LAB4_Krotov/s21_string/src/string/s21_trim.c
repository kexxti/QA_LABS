#include "s21_string.h"
#include "stdlib.h"

void *s21_trim(const char *src, const char *trim_chars) {
  void *res = S21_NULL;
  if (src && trim_chars) {
    const char *start = src + s21_strspn(src, trim_chars);
    const char *end = src + s21_strlen(src) - s21_strrspn(src, trim_chars);

    if (end <= start) {
      res = (void *)calloc(1, sizeof(char));
      if (res) {
        *(char *)res = '\0';
      }
    } else {
      s21_size_t new_len = end - start;
      res = (void *)calloc(new_len + 1, sizeof(char));
      if (res) {
        s21_strncpy(res, start, new_len);
        ((char *)res)[new_len] = '\0';
      }
    }
  }
  return res;
}