#ifndef S21_SSCANF_H
#define S21_SSCANF_H

#include <ctype.h>
#include <math.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>  // for EOF
#include <stdlib.h>

#include "s21_formatting.h"
#include "s21_string.h"
typedef struct scan_format {
  bool is_symbol;        // if *char* in format without % then it is read as is,
  char matching_symbol;  // if *char* and the read one differ scan fails

  bool ignore_whitespaces;
  bool ignore;
  s21_size_t width;
  LENGTH length_modifier;
  MODIFIER type_modifier;
} scan_format;

int s21_sscanf(const char *str, const char *format, ...);
scan_format *s21_sscanf_init_format();
void s21_sscanf_fill_format_default(scan_format *settings);
void s21_sscanf_read_format(const char **format, scan_format *settings);
LENGTH s21_sscanf_get_length(const char ch);
MODIFIER s21_sscanf_get_modifier(const char ch);
s21_size_t s21_sscanf_get_width(const char **format);
void s21_sscanf_normalize_format(scan_format *settings);
bool s21_sscanf_needs_dest(scan_format *settings);
void *s21_sscanf_get_next_dest(scan_format *settings, va_list args);
bool s21_sscanf_get_symbol(const char **str, scan_format *settings,
                           int *read_bytes_count);
bool s21_sscanf_get_char(const char **str, scan_format *settings, void *dest,
                         int *read_bytes_count);
bool s21_sscanf_is_negative_ato(s21_size_t *length, const char **str,
                                int *read_bytes_count);
void s21_sscanf_atoi_move_to_next(s21_size_t *length, const char **str,
                                  int *read_bytes_count,
                                  bool *is_scan_succeded);
int s21_atoi(const char **str, scan_format *settings, int *read_bytes_count,
             bool *is_scan_succeded);
short int s21_atosi(const char **str, scan_format *settings,
                    int *read_bytes_count, bool *is_scan_succeded);
long int s21_atol(const char **str, scan_format *settings,
                  int *read_bytes_count, bool *is_scan_succeded);
bool s21_sscanf_get_decimal(const char **str, scan_format *settings, void *dest,
                            int *read_bytes_count);
void s21_sscanf_skip_whitespaces(const char **str, int *read_bytes_count);
bool s21_sscanf_get_udecimal(const char **str, scan_format *settings,
                             void *dest, int *read_bytes_count);
int s21_a_to_octali(const char **str, scan_format *settings,
                    int *read_bytes_count, bool *is_scan_succeded);
short int s21_a_to_octalsi(const char **str, scan_format *settings,
                           int *read_bytes_count, bool *is_scan_succeded);
long int s21_a_to_octall(const char **str, scan_format *settings,
                         int *read_bytes_count, bool *is_scan_succeded);
bool s21_sscanf_get_uoctal(const char **str, scan_format *settings, void *dest,
                           int *read_bytes_count);
void s21_sscanf_skip_hex_prefix(s21_size_t *length, const char **str,
                                scan_format *settings, int *read_bytes_count);
bool s21_sscanf_skip_hex_atoi_prefixes(s21_size_t *length, const char **str,
                                       scan_format *settings,
                                       int *read_bytes_count);
int s21_a_to_hexi(const char **str, scan_format *settings,
                  int *read_bytes_count, bool *is_scan_succeded);
short int s21_a_to_hexsi(const char **str, scan_format *settings,
                         int *read_bytes_count, bool *is_scan_succeded);
long int s21_a_to_hexl(const char **str, scan_format *settings,
                       int *read_bytes_count, bool *is_scan_succeded);
bool s21_sscanf_get_uhex(const char **str, scan_format *settings, void *dest,
                         int *read_bytes_count);
bool s21_sscanf_get_integer(const char **str, scan_format *settings, void *dest,
                            int *read_bytes_count);
bool s21_sscanf_get_string(const char **str, scan_format *settings, void *dest,
                           int *read_bytes_count);
bool s21_sscanf_get_number(const char **str, scan_format *settings, void *dest,
                           int *read_bytes_count);
bool s21_sscanf_get_pointer(const char **str, scan_format *settings,
                            void **dest, int *read_bytes_count);
bool s21_sscanf_get_float(const char **str, scan_format *settings, void *dest,
                          int *read_bytes_count);
long double s21_sscanf_read_extended_double(const char **str,
                                            scan_format *settings,
                                            int *read_bytes_count,
                                            bool *is_scan_succeded);

void s21_sscanf_goto_next_char(s21_size_t *length, const char **str,
                               int *read_bytes_count);
bool s21_sscanf_get_input(const char **str, scan_format *settings, void *dest,
                          void **pointer_dest, int *read_bytes_count);

#endif