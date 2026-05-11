#include "s21_string.h"

int s21_strncmp(const char *str1, const char *str2, s21_size_t n) {
  // if (!str1 || !str2) return 0;  // Безопасность на случай передачи NULL
  unsigned char ch1 = '\0';
  unsigned char ch2 = '\0';
  int diff = 0;

  while (n > 0) {
    ch1 = (unsigned char)*str1++;
    ch2 = (unsigned char)*str2++;
    if (ch1 == '\0' || ch1 != ch2) {
      diff = ch1 - ch2;
      break;
    }
    n--;
  }
  return diff;
}
