#ifndef S21_SPRINTF_H
#define S21_SPRINTF_H

#include <ctype.h>
#include <math.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdlib.h>

#include "s21_formatting.h"
#include "s21_string.h"

typedef struct print_format {
  bool left_align;  // '-'
  bool force_sign;  // '+'
  bool space;
  bool alt_form;  // '#'
  bool zero_pad;  // '0'

  s21_size_t width;
  bool precision_specified;  // dot
  s21_size_t precision;

  LENGTH length_modifier;
  MODIFIER type_modifier;
  char spec;  // 'f', 'e', etc
} print_format;

print_format *s21_sprintf_init_format();
void s21_sprintf_fill_format_default(print_format *cf);
void s21_sprintf_read_format(const char **format, print_format *cf,
                             va_list args);
void s21_sprintf_write_symbol(const char ch, char **dest, int *written);
void s21_sprintf_parse_flags(const char **format, print_format *cf);
s21_size_t s21_sprintf_get_width(const char **format, va_list args);
void s21_sprintf_read_precision(const char **format, print_format *cf,
                                va_list args);
void s21_sprintf_read_length(const char **format, print_format *cf);
void s21_sprintf_pick_format(print_format *cf);
s21_size_t s21_sprintf_get_precision(const char **format, va_list args);
void s21_sprintf_reverse_str(char *str, int len);
int s21_sprintf_itoa_custom(long long num, char *buf, int base, bool uppercase);
int s21_sprintf_utoa_custom(unsigned long long num, char *buf, int base,
                            bool uppercase);
void s21_sprintf_apply_format(char **dest, print_format *cf, va_list args,
                              int *written);
int s21_sprintf_format(print_format *cf, va_list args, char *temp, int written);

int s21_sprintf_format_char(va_list args, char *buffer);
int s21_sprintf_format_string(print_format *cf, va_list args, char *buffer);
int s21_sprintf_format_decimal(print_format *cf, va_list args, char *buffer);
int s21_sprintf_format_unsigned(print_format *cf, va_list args, char *buffer,
                                int base, bool uppercase);
int s21_sprintf_format_sign(print_format *cf, long double val, char *buffer);
int s21_sprintf_format_fractional_part(long double frac, int prec,
                                       char *buffer);
int s21_sprintf_format_float(print_format *cf, va_list args, char *buffer);
void s21_sprintf_remove_float_zeros(print_format *cf, char *buffer, int *pos);
void s21_sprintf_format_prec(print_format *cf, char *buffer, int prec, int *pos,
                             long double rounded, long long int_part);
void s21_sprintf_format_exponent_part(char *buffer, int *exponent,
                                      bool uppercase, int *pos);
int s21_sprintf_format_default_float(print_format *cf, char *buffer,
                                     long double val, int prec);
int s21_sprintf_format_float_sci(long double val, int prec, char *buffer,
                                 bool uppercase);
int s21_sprintf_format_pointer(va_list args, char *buffer);

void s21_sprintf_write_padding(char **dest, int pad, char pad_char,
                               int *written);

#endif
