#include "s21_sscanf.h"

int s21_sscanf(const char *str, const char *format, ...) {
  int read_bytes_count = 0;
  int successful_scans_count = 0;
  bool should_return_EOF = false;
  va_list args;
  va_start(args, format);
  bool is_scan_failed = false;
  scan_format *settings = s21_sscanf_init_format();
  while (!is_scan_failed && s21_strlen(format) > 0) {
    s21_sscanf_fill_format_default(settings);
    s21_sscanf_read_format(&format, settings);
    s21_sscanf_normalize_format(settings);
    void *dest = NULL;
    void **pointer_dest = NULL;
    if (s21_sscanf_needs_dest(settings)) {
      if (settings->type_modifier == POINTER)
        pointer_dest = va_arg(args, void **);
      else
        dest = s21_sscanf_get_next_dest(settings, args);
    }
    const char *temp = str;  // to track EOF
    is_scan_failed = !s21_sscanf_get_input(&str, settings, dest, pointer_dest,
                                           &read_bytes_count);
    if (!is_scan_failed && !settings->is_symbol && !settings->ignore &&
        settings->type_modifier != NUMBER)
      successful_scans_count++;
    if (temp == str && s21_strlen(temp) == 0) should_return_EOF = true;
  }
  free(settings);
  va_end(args);
  if (successful_scans_count == 0 && should_return_EOF)
    successful_scans_count = EOF;
  return successful_scans_count;
}

scan_format *s21_sscanf_init_format() {
  scan_format *ptr = malloc(sizeof(scan_format));
  if (ptr) s21_sscanf_fill_format_default(ptr);
  return ptr;
}

void s21_sscanf_fill_format_default(scan_format *settings) {
  settings->is_symbol = false;
  settings->matching_symbol = '\0';
  settings->ignore_whitespaces = false;
  settings->ignore = false;
  settings->width = 0;
  settings->length_modifier = NONE;
  settings->type_modifier = SYMBOL;
}

void s21_sscanf_read_format(const char **format, scan_format *settings) {
  int ch;
  while (isspace((ch = **format))) {
    settings->ignore_whitespaces = true;
    (*format)++;
  }
  if (ch != '%') {
    settings->is_symbol = true;
    settings->matching_symbol = ch;
    (*format)++;
  } else {
    (*format)++;
    if (**format == '*') {
      settings->ignore = true;
      (*format)++;
    }
    settings->width = s21_sscanf_get_width(format);
    settings->length_modifier = s21_sscanf_get_length(**format);
    if (settings->length_modifier) (*format)++;
    settings->type_modifier =
        s21_sscanf_get_modifier(**format);  // what if SYMBOL ? !!!
    if (settings->type_modifier) (*format)++;
  }
}

LENGTH s21_sscanf_get_length(const char ch) {
  LENGTH mod = NONE;
  if (ch == 'h')
    mod = SHORT;
  else if (ch == 'l')
    mod = LONG;
  else if (ch == 'L')
    mod = EXTENDED_DOUBLE;
  return mod;
}

MODIFIER s21_sscanf_get_modifier(const char ch) {
  MODIFIER mod = SYMBOL;
  if (ch == 'c')
    mod = CHAR;
  else if (ch == 'd')
    mod = DECIMAL;
  else if (ch == 'i')
    mod = INTEGER;
  else if (ch == 'e' || ch == 'E' || ch == 'f' || ch == 'g' || ch == 'G')
    mod = FLOAT;
  else if (ch == 'o')
    mod = UOCTAL;
  else if (ch == 's')
    mod = STRING;
  else if (ch == 'u')
    mod = UDECIMAL;
  else if (ch == 'x' || ch == 'X')
    mod = UHEX;
  else if (ch == 'p')
    mod = POINTER;
  else if (ch == 'n')
    mod = NUMBER;
  else if (ch == '%')
    mod = PERCENT;
  return mod;
}

s21_size_t s21_sscanf_get_width(const char **format) {
  s21_size_t width = 0;
  while (isdigit(**format)) {
    width = width * 10 + (**format - '0');
    (*format)++;
  }
  return width;
}

void s21_sscanf_normalize_format(scan_format *settings) {
  // add check to width > 0 and return whether format is possible?
  if (settings->type_modifier == PERCENT) {
    settings->is_symbol = true;
    settings->matching_symbol = '%';
  }
  if (!settings->is_symbol && settings->type_modifier != CHAR &&
      settings->type_modifier != NUMBER)
    settings->ignore_whitespaces = true;
}

bool s21_sscanf_needs_dest(scan_format *settings) {
  bool result = true;
  if (settings->ignore || settings->is_symbol ||
      settings->type_modifier == PERCENT)
    result = false;
  return result;
}

void *s21_sscanf_get_next_dest(scan_format *settings, va_list args) {
  void *dest = NULL;
  if (settings->type_modifier == CHAR || settings->type_modifier == STRING) {
    if (settings->length_modifier == LONG)
      dest = va_arg(args, wchar_t *);
    else
      dest = va_arg(args, char *);
  } else if (settings->type_modifier == INTEGER ||
             settings->type_modifier == DECIMAL ||
             settings->type_modifier == NUMBER) {
    if (settings->length_modifier == NONE)
      dest = va_arg(args, int *);
    else if (settings->length_modifier == SHORT)
      dest = va_arg(args, short int *);
    else if (settings->length_modifier == LONG)
      dest = va_arg(args, long int *);
  } else if (settings->type_modifier == UOCTAL ||
             settings->type_modifier == UHEX ||
             settings->type_modifier == UDECIMAL) {
    if (settings->length_modifier == NONE)
      dest = va_arg(args, unsigned int *);
    else if (settings->length_modifier == SHORT)
      dest = va_arg(args, unsigned short int *);
    else if (settings->length_modifier == LONG)
      dest = va_arg(args, unsigned long int *);
  } else if (settings->type_modifier == FLOAT) {
    if (settings->length_modifier == NONE)
      dest = va_arg(args, float *);
    else if (settings->length_modifier == LONG)
      dest = va_arg(args, double *);
    else if (settings->length_modifier == EXTENDED_DOUBLE)
      dest = va_arg(args, long double *);
  }
  return dest;
}

bool s21_sscanf_get_symbol(const char **str, scan_format *settings,
                           int *read_bytes_count) {
  bool is_scan_succeded = false;
  if (settings->ignore_whitespaces)
    s21_sscanf_skip_whitespaces(str, read_bytes_count);
  if ((*str)[0] == settings->matching_symbol) {
    is_scan_succeded = true;
    s21_sscanf_goto_next_char(NULL, str, read_bytes_count);
  }
  return is_scan_succeded;
}

bool s21_sscanf_get_char(const char **str, scan_format *settings, void *dest,
                         int *read_bytes_count) {
  bool is_scan_succeded = false;
  if (settings->ignore_whitespaces)
    s21_sscanf_skip_whitespaces(str, read_bytes_count);
  if (settings->length_modifier == NONE) {
    char ch = **str;
    if (ch) {
      is_scan_succeded = true;
      s21_sscanf_goto_next_char(NULL, str, read_bytes_count);
      if (!settings->ignore) *((char *)dest) = ch;
    }
  } else if (settings->length_modifier == LONG) {
    wchar_t ch = **str;
    if (ch) {
      is_scan_succeded = true;
      s21_sscanf_goto_next_char(NULL, str, read_bytes_count);
      if (!settings->ignore) *((wchar_t *)dest) = ch;
    }
  }
  return is_scan_succeded;
}

bool s21_sscanf_is_negative_ato(s21_size_t *length, const char **str,
                                int *read_bytes_count) {
  bool negative = false;
  if (**str == '-') {
    s21_sscanf_goto_next_char(length, str, read_bytes_count);
    negative = true;
  } else if (**str == '+')
    s21_sscanf_goto_next_char(length, str, read_bytes_count);
  return negative;
}

void s21_sscanf_atoi_move_to_next(s21_size_t *length, const char **str,
                                  int *read_bytes_count,
                                  bool *is_scan_succeded) {
  s21_sscanf_goto_next_char(length, str, read_bytes_count);
  if (!*is_scan_succeded) *is_scan_succeded = true;
}
int s21_atoi(const char **str, scan_format *settings, int *read_bytes_count,
             bool *is_scan_succeded) {
  int result = 0;
  s21_size_t length = 0;
  bool negative = s21_sscanf_is_negative_ato(&length, str, read_bytes_count);
  while (isdigit(**str) && (length < settings->width || !settings->width)) {
    result = result * 10 + (**str - '0');
    s21_sscanf_atoi_move_to_next(&length, str, read_bytes_count,
                                 is_scan_succeded);
  }
  if (negative) result *= -1;
  return result;
}

short int s21_atosi(const char **str, scan_format *settings,
                    int *read_bytes_count, bool *is_scan_succeded) {
  short int result = 0;
  s21_size_t length = 0;
  bool negative = s21_sscanf_is_negative_ato(&length, str, read_bytes_count);
  while (isdigit(**str) && (length < settings->width || !settings->width)) {
    result = result * 10 + (**str - '0');
    s21_sscanf_atoi_move_to_next(&length, str, read_bytes_count,
                                 is_scan_succeded);
  }
  if (negative) result *= -1;
  return result;
}

long int s21_atol(const char **str, scan_format *settings,
                  int *read_bytes_count, bool *is_scan_succeded) {
  long int result = 0;
  s21_size_t length = 0;
  bool negative = s21_sscanf_is_negative_ato(&length, str, read_bytes_count);
  while (isdigit(**str) && (length < settings->width || !settings->width)) {
    result = result * 10 + (**str - '0');
    s21_sscanf_atoi_move_to_next(&length, str, read_bytes_count,
                                 is_scan_succeded);
  }
  if (negative) result *= -1;
  return result;
}

bool s21_sscanf_get_decimal(const char **str, scan_format *settings, void *dest,
                            int *read_bytes_count) {
  bool is_scan_succeded = false;
  if (settings->ignore_whitespaces)
    s21_sscanf_skip_whitespaces(str, read_bytes_count);
  if (settings->length_modifier == NONE) {
    int value = s21_atoi(str, settings, read_bytes_count, &is_scan_succeded);
    if (is_scan_succeded && !settings->ignore) *(int *)dest = value;
  } else if (settings->length_modifier == SHORT) {
    short int value =
        s21_atosi(str, settings, read_bytes_count, &is_scan_succeded);
    if (is_scan_succeded && !settings->ignore) *(short int *)dest = value;
  } else if (settings->length_modifier == LONG) {
    long int value =
        s21_atol(str, settings, read_bytes_count, &is_scan_succeded);
    if (is_scan_succeded && !settings->ignore) *(long int *)dest = value;
  }
  return is_scan_succeded;
}

void s21_sscanf_skip_whitespaces(const char **str, int *read_bytes_count) {
  while (isspace(**str)) s21_sscanf_goto_next_char(NULL, str, read_bytes_count);
}

bool s21_sscanf_get_udecimal(const char **str, scan_format *settings,
                             void *dest, int *read_bytes_count) {
  bool is_scan_succeded = false;
  if (settings->ignore_whitespaces)
    s21_sscanf_skip_whitespaces(str, read_bytes_count);
  if (settings->length_modifier == NONE) {  // seriosly lol, only cast
    unsigned int value = (unsigned int)s21_atoi(str, settings, read_bytes_count,
                                                &is_scan_succeded);
    if (is_scan_succeded && !settings->ignore) *(unsigned int *)dest = value;
  } else if (settings->length_modifier == SHORT) {
    unsigned short int value = (unsigned short int)s21_atosi(
        str, settings, read_bytes_count, &is_scan_succeded);
    if (is_scan_succeded && !settings->ignore)
      *(unsigned short int *)dest = value;
  } else if (settings->length_modifier == LONG) {
    unsigned long int value = (unsigned long int)s21_atol(
        str, settings, read_bytes_count, &is_scan_succeded);
    if (is_scan_succeded && !settings->ignore)
      *(unsigned long int *)dest = value;
  }
  return is_scan_succeded;
}

int s21_a_to_octali(const char **str, scan_format *settings,
                    int *read_bytes_count, bool *is_scan_succeded) {
  int result = 0;
  s21_size_t length = 0;
  bool negative = s21_sscanf_is_negative_ato(&length, str, read_bytes_count);
  while (**str < '8' && **str >= '0' &&
         (length < settings->width || !settings->width)) {
    result = result * 8 + (**str - '0');
    s21_sscanf_atoi_move_to_next(&length, str, read_bytes_count,
                                 is_scan_succeded);
  }
  if (negative) result *= -1;
  return result;
}
short int s21_a_to_octalsi(const char **str, scan_format *settings,
                           int *read_bytes_count, bool *is_scan_succeded) {
  short int result = 0;
  s21_size_t length = 0;
  bool negative = s21_sscanf_is_negative_ato(&length, str, read_bytes_count);
  while (**str < '8' && **str >= '0' &&
         (length < settings->width || !settings->width)) {
    result = result * 8 + (**str - '0');
    s21_sscanf_atoi_move_to_next(&length, str, read_bytes_count,
                                 is_scan_succeded);
  }
  if (negative) result *= -1;
  return result;
}
long int s21_a_to_octall(const char **str, scan_format *settings,
                         int *read_bytes_count, bool *is_scan_succeded) {
  long int result = 0;
  s21_size_t length = 0;
  bool negative = s21_sscanf_is_negative_ato(&length, str, read_bytes_count);
  while (**str < '8' && **str >= '0' &&
         (length < settings->width || !settings->width)) {
    result = result * 8 + (**str - '0');
    s21_sscanf_atoi_move_to_next(&length, str, read_bytes_count,
                                 is_scan_succeded);
  }
  if (negative) result *= -1;
  return result;
}

bool s21_sscanf_get_uoctal(const char **str, scan_format *settings, void *dest,
                           int *read_bytes_count) {
  bool is_scan_succeded = false;
  if (settings->ignore_whitespaces)
    s21_sscanf_skip_whitespaces(str, read_bytes_count);
  if (settings->length_modifier == NONE) {
    unsigned int value =
        s21_a_to_octali(str, settings, read_bytes_count, &is_scan_succeded);
    if (is_scan_succeded && !settings->ignore) *(unsigned int *)dest = value;
  } else if (settings->length_modifier == SHORT) {
    unsigned short int value =
        s21_a_to_octalsi(str, settings, read_bytes_count, &is_scan_succeded);
    if (is_scan_succeded && !settings->ignore)
      *(unsigned short int *)dest = value;
  } else if (settings->length_modifier == LONG) {
    unsigned long int value =
        s21_a_to_octall(str, settings, read_bytes_count, &is_scan_succeded);
    if (is_scan_succeded && !settings->ignore)
      *(unsigned long int *)dest = value;
  }
  return is_scan_succeded;
}

void s21_sscanf_skip_hex_prefix(s21_size_t *length, const char **str,
                                scan_format *settings, int *read_bytes_count) {
  if (s21_strlen(*str) >= 2 && (*str)[0] == '0' &&
      ((*str)[1] == 'x' || (*str)[1] == 'X')) {
    s21_size_t delta =
        settings->width >= 2 || !settings->width ? 2 : settings->width;
    (*str) += delta;
    (*read_bytes_count) += delta;
    (*length) += delta;
  }
}

bool s21_sscanf_skip_hex_atoi_prefixes(s21_size_t *length, const char **str,
                                       scan_format *settings,
                                       int *read_bytes_count) {
  bool negative = s21_sscanf_is_negative_ato(length, str, read_bytes_count);
  s21_sscanf_skip_hex_prefix(length, str, settings, read_bytes_count);
  return negative;
}

int s21_a_to_hexi(const char **str, scan_format *settings,
                  int *read_bytes_count, bool *is_scan_succeded) {
  int result = 0;
  s21_size_t length = 0;
  bool negative = s21_sscanf_skip_hex_atoi_prefixes(&length, str, settings,
                                                    read_bytes_count);
  while (((tolower(**str) <= 'f' && tolower(**str) >= 'a') || isdigit(**str)) &&
         (length < settings->width || !settings->width)) {
    result = result * 16;
    if (isdigit(**str))
      result += (**str - '0');
    else
      result += (tolower(**str) - 'a' + 10);
    s21_sscanf_atoi_move_to_next(&length, str, read_bytes_count,
                                 is_scan_succeded);
  }
  if (negative) result *= -1;
  return result;
}
short int s21_a_to_hexsi(const char **str, scan_format *settings,
                         int *read_bytes_count, bool *is_scan_succeded) {
  short int result = 0;
  s21_size_t length = 0;
  bool negative = s21_sscanf_skip_hex_atoi_prefixes(&length, str, settings,
                                                    read_bytes_count);
  while (((tolower(**str) <= 'f' && tolower(**str) >= 'a') || isdigit(**str)) &&
         (length < settings->width || !settings->width)) {
    result = result * 16;
    if (isdigit(**str))
      result += (**str - '0');
    else
      result += (tolower(**str) - 'a' + 10);
    s21_sscanf_atoi_move_to_next(&length, str, read_bytes_count,
                                 is_scan_succeded);
  }
  if (negative) result *= -1;
  return result;
}
long int s21_a_to_hexl(const char **str, scan_format *settings,
                       int *read_bytes_count, bool *is_scan_succeded) {
  long int result = 0;
  s21_size_t length = 0;
  bool negative = s21_sscanf_skip_hex_atoi_prefixes(&length, str, settings,
                                                    read_bytes_count);
  while (((tolower(**str) <= 'f' && tolower(**str) >= 'a') || isdigit(**str)) &&
         (length < settings->width || !settings->width)) {
    result = result * 16;
    if (isdigit(**str))
      result += (**str - '0');
    else
      result += (tolower(**str) - 'a' + 10);
    s21_sscanf_atoi_move_to_next(&length, str, read_bytes_count,
                                 is_scan_succeded);
  }
  if (negative) result *= -1;
  return result;
}

bool s21_sscanf_get_uhex(const char **str, scan_format *settings, void *dest,
                         int *read_bytes_count) {
  bool is_scan_succeded = false;
  if (settings->ignore_whitespaces)
    s21_sscanf_skip_whitespaces(str, read_bytes_count);

  bool has_prefix = false;
  if (s21_strlen(*str) >= 2 && (*str)[0] == '0' &&
      ((*str)[1] == 'x' || (*str)[1] == 'X'))
    has_prefix = true;

  if (settings->length_modifier == NONE) {
    unsigned int value =
        s21_a_to_hexi(str, settings, read_bytes_count, &is_scan_succeded);
    if (is_scan_succeded && !settings->ignore)
      *(unsigned int *)dest = value;
    else if (has_prefix && !settings->ignore)
      *(unsigned int *)dest = 0;
  } else if (settings->length_modifier == SHORT) {
    unsigned short int value =
        s21_a_to_hexsi(str, settings, read_bytes_count, &is_scan_succeded);
    if (is_scan_succeded && !settings->ignore)
      *(unsigned short int *)dest = value;
    else if (has_prefix && !settings->ignore)
      *(unsigned short int *)dest = 0;
  } else if (settings->length_modifier == LONG) {
    unsigned long int value =
        s21_a_to_hexl(str, settings, read_bytes_count, &is_scan_succeded);
    if (is_scan_succeded && !settings->ignore)
      *(unsigned long int *)dest = value;
    else if (has_prefix && !settings->ignore)
      *(unsigned long int *)dest = 0;
  }
  if (has_prefix) is_scan_succeded = true;
  return is_scan_succeded;
}

bool s21_sscanf_get_integer(const char **str, scan_format *settings, void *dest,
                            int *read_bytes_count) {
  bool is_scan_succeded = false;

  if (**str == '0') {
    if ((*str)[1] == 'x' || (*str)[1] == 'X')
      is_scan_succeded =
          s21_sscanf_get_uhex(str, settings, dest, read_bytes_count);
    else
      is_scan_succeded =
          s21_sscanf_get_uoctal(str, settings, dest, read_bytes_count);
  } else
    is_scan_succeded =
        s21_sscanf_get_decimal(str, settings, dest, read_bytes_count);

  return is_scan_succeded;
}

bool s21_sscanf_get_string(const char **str, scan_format *settings, void *dest,
                           int *read_bytes_count) {
  bool is_scan_succeded = false;
  if (settings->ignore_whitespaces)
    s21_sscanf_skip_whitespaces(str, read_bytes_count);
  char *result;
  if (!settings->ignore) result = (char *)dest;
  s21_size_t length = 0;
  while (!isspace(**str) && **str != '\0' &&
         (!settings->width || length < settings->width)) {
    if (!settings->ignore) {
      *result = **str;
      result++;
    }
    s21_sscanf_goto_next_char(&length, str, read_bytes_count);
  }
  if (!settings->ignore && length) *result = '\0';
  if (length) is_scan_succeded = true;
  return is_scan_succeded;
}

bool s21_sscanf_get_number(const char **str, scan_format *settings, void *dest,
                           int *read_bytes_count) {
  if (settings->ignore_whitespaces)
    s21_sscanf_skip_whitespaces(str, read_bytes_count);
  if (settings->length_modifier == NONE) *(int *)dest = *read_bytes_count;
  if (settings->length_modifier == SHORT)
    *(short int *)dest = *read_bytes_count;
  if (settings->length_modifier == LONG) *(long int *)dest = *read_bytes_count;
  return true;
}

bool s21_sscanf_get_pointer(const char **str, scan_format *settings,
                            void **dest, int *read_bytes_count) {
  bool is_scan_succeded = false;
  if (settings->ignore_whitespaces)
    s21_sscanf_skip_whitespaces(str, read_bytes_count);
  bool has_prefix = false;
  if (**str == '0') has_prefix = true;
  unsigned long int value = (unsigned long int)s21_a_to_hexl(
      str, settings, read_bytes_count, &is_scan_succeded);  // it's always hex
  if (is_scan_succeded && !settings->ignore) {
    *dest = (void *)value;
  } else if (has_prefix && !settings->ignore)
    *dest = (void *)0;
  if (has_prefix) is_scan_succeded = true;
  return is_scan_succeded;
}

bool s21_sscanf_get_float(const char **str, scan_format *settings, void *dest,
                          int *read_bytes_count) {
  bool is_scan_succeded = false;
  if (settings->ignore_whitespaces)
    s21_sscanf_skip_whitespaces(str, read_bytes_count);
  if (settings->length_modifier == NONE) {
    float value = s21_sscanf_read_extended_double(
        str, settings, read_bytes_count, &is_scan_succeded);
    if (is_scan_succeded && !settings->ignore) *(float *)dest = value;
  }
  if (settings->length_modifier == LONG) {
    double value = s21_sscanf_read_extended_double(
        str, settings, read_bytes_count, &is_scan_succeded);
    if (is_scan_succeded && !settings->ignore) *(double *)dest = value;
  }
  if (settings->length_modifier == EXTENDED_DOUBLE) {
    long double value = s21_sscanf_read_extended_double(
        str, settings, read_bytes_count, &is_scan_succeded);
    if (is_scan_succeded && !settings->ignore) *(long double *)dest = value;
  }
  return is_scan_succeded;
}

long double s21_sscanf_read_extended_double(const char **str,
                                            scan_format *settings,
                                            int *read_bytes_count,
                                            bool *is_scan_succeded) {
  long double result = 0.0;
  s21_size_t length = 0;
  bool negative = s21_sscanf_is_negative_ato(&length, str, read_bytes_count);
  while (isdigit(**str) && (length < settings->width || !settings->width)) {
    result = result * 10.0 + (**str - '0');
    s21_sscanf_goto_next_char(&length, str, read_bytes_count);
    if (!*is_scan_succeded) *is_scan_succeded = true;
  }
  if (**str == '.' && (length < settings->width || !settings->width)) {
    s21_sscanf_goto_next_char(&length, str, read_bytes_count);
    if (!*is_scan_succeded && isdigit(**str)) *is_scan_succeded = true;
  }
  short exponent = 0;
  while (isdigit(**str) && (length < settings->width || !settings->width)) {
    result = result * 10.0 + (**str - '0');
    exponent--;
    s21_sscanf_goto_next_char(&length, str, read_bytes_count);
  }

  if (tolower(**str) == 'e' && (length < settings->width || !settings->width)) {
    s21_sscanf_goto_next_char(&length, str, read_bytes_count);
    short additional_exponent = 0;
    bool is_exponent_negative =
        s21_sscanf_is_negative_ato(&length, str, read_bytes_count);
    while (isdigit(**str) && (length < settings->width || !settings->width)) {
      additional_exponent = additional_exponent * 10 + (**str - '0');
      s21_sscanf_goto_next_char(&length, str, read_bytes_count);
    }
    if (is_exponent_negative) additional_exponent *= -1;
    exponent += additional_exponent;
  }

  result *= pow(10, exponent);

  if (negative) result *= -1;
  return result;
}

void s21_sscanf_goto_next_char(s21_size_t *length, const char **str,
                               int *read_bytes_count) {
  (*str)++;
  (*read_bytes_count)++;
  if (length) (*length)++;  // chars don't need width
}

bool s21_sscanf_get_input(const char **str, scan_format *settings, void *dest,
                          void **pointer_dest, int *read_bytes_count) {
  bool is_scan_succeded = false;
  if (settings->is_symbol)
    is_scan_succeded = s21_sscanf_get_symbol(str, settings, read_bytes_count);
  else {
    if (settings->type_modifier == CHAR)
      is_scan_succeded =
          s21_sscanf_get_char(str, settings, dest, read_bytes_count);
    if (settings->type_modifier == DECIMAL)
      is_scan_succeded =
          s21_sscanf_get_decimal(str, settings, dest, read_bytes_count);
    if (settings->type_modifier == INTEGER)
      is_scan_succeded =
          s21_sscanf_get_integer(str, settings, dest, read_bytes_count);
    if (settings->type_modifier == FLOAT)
      is_scan_succeded =
          s21_sscanf_get_float(str, settings, dest, read_bytes_count);
    if (settings->type_modifier == UOCTAL)
      is_scan_succeded =
          s21_sscanf_get_uoctal(str, settings, dest, read_bytes_count);
    if (settings->type_modifier == STRING)
      is_scan_succeded =
          s21_sscanf_get_string(str, settings, dest, read_bytes_count);
    if (settings->type_modifier == UDECIMAL)
      is_scan_succeded =
          s21_sscanf_get_udecimal(str, settings, dest, read_bytes_count);
    if (settings->type_modifier == UHEX)
      is_scan_succeded =
          s21_sscanf_get_uhex(str, settings, dest, read_bytes_count);
    if (settings->type_modifier == POINTER)
      is_scan_succeded =
          s21_sscanf_get_pointer(str, settings, pointer_dest, read_bytes_count);
    if (settings->type_modifier == NUMBER)
      is_scan_succeded =
          s21_sscanf_get_number(str, settings, dest, read_bytes_count);
  }
  return is_scan_succeded;
}