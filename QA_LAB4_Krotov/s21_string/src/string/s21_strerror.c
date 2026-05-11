#include "s21_strerror.h"

char *s21_strerror(int errnum) {
  static char buff[256];
  if (errnum >= 0 && errnum < (int)(sizeof(S21_ERRORS) / sizeof(S21_ERRORS[0])))
    s21_memcpy(buff, S21_ERRORS[errnum], s21_strlen(S21_ERRORS[errnum]) + 1);
  else {
#ifdef __linux__
    s21_sprintf(buff, "Unknown error %d", errnum);
#elif defined(__APPLE__)
    s21_sprintf(buff, "Unknown error: %d", errnum);
#endif
  }
  return buff;
}