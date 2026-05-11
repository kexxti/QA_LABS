#include "s21_string.h"

char *s21_strstr(const char *haystack, const char *needle) {
  char *result = S21_NULL;
  if (*needle != '\0') {
    const char *h;
    const char *n;
    while (*haystack && result == S21_NULL) {
      h = haystack;
      n = needle;
      while (*h && *n && (*h == *n)) {
        h++;
        n++;
      }
      if (*n == '\0') {
        result = (char *)haystack;
      }
      haystack++;
    }
  } else {
    result = (char *)haystack;
  }
  return result;
}
