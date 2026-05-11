#include "s21_sprintf.h"

int s21_sprintf(char *str, const char *format, ...) {
  va_list args;
  va_start(args, format);
  int written = 0;
  char *dest = str;
  print_format *cf = s21_sprintf_init_format();  // mem alloc is expensive
  while (*format) {
    s21_sprintf_fill_format_default(cf);
    s21_sprintf_read_format(&format, cf, args);
    s21_sprintf_apply_format(&dest, cf, args, &written);
  }
  free(cf);
  *dest = '\0';
  va_end(args);
  return written;
}

void s21_sprintf_write_symbol(const char ch, char **dest, int *written) {
  **dest = ch;
  (*dest)++;
  (*written)++;
}

print_format *s21_sprintf_init_format() {
  print_format *cf = (print_format *)malloc(sizeof(print_format));
  if (cf) s21_sprintf_fill_format_default(cf);
  return cf;
}

void s21_sprintf_fill_format_default(print_format *cf) {
  cf->left_align = false;
  cf->force_sign = false;
  cf->space = false;
  cf->alt_form = false;
  cf->zero_pad = false;
  cf->width = 0;
  cf->precision_specified = false;
  cf->precision = 0;
  cf->length_modifier = NONE;
  cf->type_modifier = SYMBOL;
  cf->spec = '\0';
}

void s21_sprintf_read_precision(const char **format, print_format *cf,
                                va_list args) {
  if (**format == '.') {
    (*format)++;
    cf->precision_specified = true;
    cf->precision = s21_sprintf_get_precision(format, args);
  }
}

void s21_sprintf_read_length(const char **format, print_format *cf) {
  if (**format == 'h' || **format == 'l' || **format == 'L') {
    cf->length_modifier =
        (**format == 'h' ? SHORT : (**format == 'l' ? LONG : EXTENDED_DOUBLE));
    (*format)++;
  }
}

void s21_sprintf_pick_format(print_format *cf) {
  if (cf->spec == 'c') {
    cf->type_modifier = CHAR;
  } else if (cf->spec == 's') {
    cf->type_modifier = STRING;
  } else if (cf->spec == 'd' || cf->spec == 'i') {
    cf->type_modifier = DECIMAL;
  } else if (cf->spec == 'u') {
    cf->type_modifier = UDECIMAL;
  } else if (cf->spec == 'o') {
    cf->type_modifier = UOCTAL;
  } else if (cf->spec == 'x' || cf->spec == 'X') {
    cf->type_modifier = UHEX;
  } else if (cf->spec == 'p') {
    cf->type_modifier = POINTER;
  } else if (cf->spec == 'n') {
    cf->type_modifier = NUMBER;
  } else if (cf->spec == 'f' || cf->spec == 'e' || cf->spec == 'E' ||
             cf->spec == 'g' || cf->spec == 'G') {
    cf->type_modifier = FLOAT;
  } else if (cf->spec == '%') {
    cf->type_modifier = PERCENT;
  } else {
    cf->type_modifier = SYMBOL;
  }
}

void s21_sprintf_read_format(const char **format, print_format *cf,
                             va_list args) {
  if (**format == '%') {
    (*format)++;  // skip initial '%'
    s21_sprintf_parse_flags(format, cf);
    cf->width = s21_sprintf_get_width(format, args);
    s21_sprintf_read_precision(format, cf, args);
    s21_sprintf_read_length(format, cf);
    cf->spec = **format;
    s21_sprintf_pick_format(cf);
  } else {
    cf->spec = **format;
    cf->type_modifier = SYMBOL;
  }
  if (**format) (*format)++;
}

bool is_additional_format(char c) {
  return c == '-' || c == '+' || c == ' ' || c == '#' || c == '0';
}

void s21_sprintf_parse_flags(const char **format, print_format *cf) {
  char ch;
  while ((ch = **format) && is_additional_format(ch)) {
    if (ch == '-')
      cf->left_align = true;
    else if (ch == '+')
      cf->force_sign = true;
    else if (ch == ' ')
      cf->space = true;
    else if (ch == '#')
      cf->alt_form = true;
    else if (ch == '0')
      cf->zero_pad = true;
    (*format)++;
  }
}

s21_size_t s21_sprintf_get_width(const char **format, va_list args) {
  s21_size_t width = 0;
  if (**format == '*') {
    width = (s21_size_t)va_arg(args, int);
    (*format)++;
  } else {
    while (isdigit(**format)) {
      width = width * 10 + (**format - '0');
      (*format)++;
    }
  }
  return width;
}

s21_size_t s21_sprintf_get_precision(const char **format, va_list args) {
  s21_size_t precision = 0;
  if (**format == '*') {
    precision = (s21_size_t)va_arg(args, int);
    (*format)++;
  } else {
    while (isdigit(**format)) {
      precision = precision * 10 + (**format - '0');
      (*format)++;
    }
  }
  return precision;
}

void s21_sprintf_reverse_str(char *str, int len) {
  int i = 0, j = len - 1;
  while (i < j) {
    char tmp = str[i];
    str[i] = str[j];
    str[j] = tmp;
    i++;
    j--;
  }
}

int s21_sprintf_itoa_custom(long long num, char *buf, int base,
                            bool uppercase) {
  int i = 0;
  bool neg = false;
  if (num < 0 && base == 10) {
    neg = true;
    num = -num;
  }
  if (num == 0) {
    buf[i++] = '0';
  } else {
    while (num) {
      int remain = num % base;
      buf[i++] = (remain < 10) ? ('0' + remain)
                               : ((uppercase ? 'A' : 'a') + remain - 10);
      num /= base;
    }
    if (neg) buf[i++] = '-';
  }
  s21_sprintf_reverse_str(buf, i);
  buf[i] = '\0';
  return i;
}

int s21_sprintf_utoa_custom(unsigned long long num, char *buf, int base,
                            bool uppercase) {
  int i = 0;
  if (num == 0) {
    buf[i++] = '0';
  } else {
    while (num) {
      int remain = num % base;
      buf[i++] = (remain < 10) ? ('0' + remain)
                               : ((uppercase ? 'A' : 'a') + remain - 10);
      num /= base;
    }
  }
  s21_sprintf_reverse_str(buf, i);
  buf[i] = '\0';
  return i;
}

int s21_sprintf_format(print_format *cf, va_list args, char *temp,
                       int written) {
  int len = 0;
  if (cf->type_modifier == CHAR) {
    len = s21_sprintf_format_char(args, temp);
  } else if (cf->type_modifier == STRING) {
    len = s21_sprintf_format_string(cf, args, temp);
  } else if (cf->type_modifier == DECIMAL || cf->type_modifier == INTEGER) {
    len = s21_sprintf_format_decimal(cf, args, temp);
  } else if (cf->type_modifier == UDECIMAL) {
    len = s21_sprintf_format_unsigned(cf, args, temp, 10, false);
  } else if (cf->type_modifier == UOCTAL) {
    len = s21_sprintf_format_unsigned(cf, args, temp, 8, false);
  } else if (cf->type_modifier == UHEX) {
    bool up = (cf->spec == 'X');
    len = s21_sprintf_format_unsigned(cf, args, temp, 16, up);
  } else if (cf->type_modifier == POINTER) {
    len = s21_sprintf_format_pointer(args, temp);
  } else if (cf->type_modifier == FLOAT) {
    len = s21_sprintf_format_float(cf, args, temp);
  } else if (cf->type_modifier == NUMBER) {
    int *n_ptr = va_arg(args, int *);
    if (n_ptr) *n_ptr = written;
  }
  return len;
}

void s21_sprintf_apply_format(char **dest, print_format *cf, va_list args,
                              int *written) {
  if (cf->type_modifier == SYMBOL || cf->type_modifier == PERCENT) {
    s21_sprintf_write_symbol(cf->spec, dest, written);
  } else {
    char temp[1024] = {0};
    int len = s21_sprintf_format(cf, args, temp, *written);
    int padding = (cf->width > (s21_size_t)len) ? cf->width - len : 0;
    if (!cf->left_align)
      s21_sprintf_write_padding(
          dest, padding, (cf->zero_pad && !cf->precision_specified) ? '0' : ' ',
          written);
    s21_memcpy(*dest, temp, len);
    *dest += len;
    *written += len;
    if (cf->left_align) s21_sprintf_write_padding(dest, padding, ' ', written);
  }
}

int s21_sprintf_format_char(va_list args, char *buffer) {
  char ch = (char)va_arg(args, int);
  buffer[0] = ch;
  buffer[1] = '\0';
  return 1;
}

int s21_sprintf_format_string(print_format *cf, va_list args, char *buffer) {
  char *s = va_arg(args, char *);
  if (!s) s = "(null)";
  int i = 0;
  while (s[i] && (!cf->precision_specified || i < (int)cf->precision)) {
    buffer[i] = s[i];
    i++;
  }
  buffer[i] = '\0';
  return i;
}

int s21_sprintf_format_decimal(print_format *cf, va_list args, char *buffer) {
  int is_negative = 0;
  long long num;
  if (cf->length_modifier == LONG)
    num = va_arg(args, long int);
  else if (cf->length_modifier == SHORT)
    num = va_arg(args, int);  // short int == int when used with va_arg
  else
    num = va_arg(args, int);
  if (num < 0) {
    is_negative = 1;
    num = -num;
  }
  char num_buf[128] = {0};
  int num_len = s21_sprintf_itoa_custom(num, num_buf, 10, false);
  int prec_num_of_zeros = 0;
  if (cf->precision_specified && cf->precision > (s21_size_t)num_len)
    prec_num_of_zeros = cf->precision - num_len;
  int pos = 0;
  if (is_negative)
    buffer[pos++] = '-';
  else if (cf->force_sign)
    buffer[pos++] = '+';
  else if (cf->space)
    buffer[pos++] = ' ';
  for (int i = 0; i < prec_num_of_zeros; i++) {
    buffer[pos++] = '0';
  }
  for (int i = 0; i < num_len; i++) {
    buffer[pos++] = num_buf[i];
  }
  buffer[pos] = '\0';
  return pos;
}

int s21_sprintf_format_unsigned(print_format *cf, va_list args, char *buffer,
                                int base, bool uppercase) {
  unsigned long long num;
  if (cf->length_modifier == LONG)
    num = va_arg(args, unsigned long);
  else if (cf->length_modifier == SHORT)
    num = (unsigned short)va_arg(args, unsigned int);
  else
    num = va_arg(args, unsigned int);
  int len = s21_sprintf_utoa_custom(num, buffer, base, uppercase);
  // oct and hex
  if (cf->alt_form) {
    if (base == 8 && buffer[0] != '0') {
      for (int i = len; i >= 0; i--) buffer[i + 1] = buffer[i];
      buffer[0] = '0';
      len++;
    } else if (base == 16 && num != 0) {
      for (int i = len; i >= 0; i--) buffer[i + 2] = buffer[i];
      buffer[0] = '0';
      buffer[1] = (uppercase ? 'X' : 'x');
      len += 2;
    }
  }
  return len;
}

int s21_sprintf_format_sign(print_format *cf, long double val, char *buffer) {
  int pos = 0;
  if (val < 0)
    buffer[pos++] = '-';
  else if (cf->force_sign)
    buffer[pos++] = '+';
  else if (cf->space)
    buffer[pos++] = ' ';
  return pos;
}

int s21_sprintf_format_fractional_part(long double frac, int prec,
                                       char *buffer) {
  int pos = 0;
  long double mult = powl(10, prec);
  long long frac_int = (long long)roundl(frac * mult);
  char frac_buf[64] = {0};
  int frac_len = s21_sprintf_utoa_custom(frac_int, frac_buf, 10, false);
  // leading zeros if needed
  while (frac_len < prec) {
    buffer[pos++] = '0';
    prec--;
  }
  s21_memcpy(buffer + pos, frac_buf, frac_len);
  pos += frac_len;
  return pos;
}

void s21_sprintf_remove_float_zeros(print_format *cf, char *buffer, int *pos) {
  if (cf->spec == 'g' || cf->spec == 'G') {
    int len = s21_strlen(buffer);
    while (len > 0 && buffer[len - 1] == '0') len--;
    if (len > 0 && buffer[len - 1] == '.') len--;
    buffer[len] = '\0';
    *pos = len;
  }
}

void s21_sprintf_format_prec(print_format *cf, char *buffer, int prec, int *pos,
                             long double rounded, long long int_part) {
  if (prec > 0 ||
      (cf->alt_form && cf->precision_specified && cf->precision == 0)) {
    buffer[(*pos)++] = '.';
    if (prec > 0) {
      long double frac = rounded - int_part;
      *pos += s21_sprintf_format_fractional_part(frac, prec, buffer + *pos);
    }
  }
  buffer[*pos] = '\0';
}

int s21_sprintf_format_default_float(print_format *cf, char *buffer,
                                     long double val, int prec) {
  int pos = 0;
  long double abs_val = fabsl(val);
  long double mult = powl(10, prec);
  long double rounded = floorl(abs_val * mult + 0.5L) / mult;

  if (cf->precision_specified && cf->precision == 1 &&
      ((long long)roundl((rounded - (long long)rounded) * mult)) == 0)
    prec = 0;

  pos += s21_sprintf_format_sign(cf, val, buffer);
  long long int_part = (long long)rounded;
  pos += s21_sprintf_itoa_custom(int_part, buffer + pos, 10, false);
  s21_sprintf_format_prec(cf, buffer, prec, &pos, rounded, int_part);
  s21_sprintf_remove_float_zeros(cf, buffer, &pos);
  return pos;
}

int s21_sprintf_format_float(print_format *cf, va_list args, char *buffer) {
  long double val = (cf->length_modifier == EXTENDED_DOUBLE)
                        ? va_arg(args, long double)
                        : (long double)va_arg(args, double);
  int prec = cf->precision_specified ? cf->precision : 6;
  int pos = 0;
  if (cf->spec == 'e' || cf->spec == 'E')
    pos = s21_sprintf_format_float_sci(val, prec, buffer, (cf->spec == 'E'));
  else if (cf->spec == 'g' || cf->spec == 'G') {
    long double abs_val = fabsl(val);
    int exponent = (abs_val > 0) ? (int)floorl(log10l(abs_val)) : 0;
    if (exponent < -4 || exponent >= prec)
      pos = s21_sprintf_format_float_sci(val, prec - 1, buffer,
                                         (cf->spec == 'G'));
    else
      pos = s21_sprintf_format_default_float(cf, buffer, val, prec);
  } else
    pos = s21_sprintf_format_default_float(cf, buffer, val, prec);
  return pos;
}

long double s21_sprintf_float_norm(long double val, int *exponent) {
  long double norm = val;
  while (val != 0.0 && norm >= 10.0) {
    norm /= 10.0;
    (*exponent)++;
  }
  while (val != 0.0 && norm < 1.0) {
    norm *= 10.0;
    (*exponent)--;
  }
  return norm;
}

void s21_sprintf_format_exponent_part(char *buffer, int *exponent,
                                      bool uppercase, int *pos) {
  buffer[(*pos)++] = (uppercase ? 'E' : 'e');
  buffer[(*pos)++] = (*exponent < 0) ? '-' : '+';
  if (*exponent < 0) *exponent = -*exponent;
  if (*exponent < 10) buffer[(*pos)++] = '0';
}

int s21_sprintf_format_float_sci(long double val, int prec, char *buffer,
                                 bool uppercase) {
  int pos = 0;
  if (val < 0) {
    buffer[pos++] = '-';
    val = -val;
  }
  int exponent = 0;
  long double norm = s21_sprintf_float_norm(val, &exponent);
  long double mult = powl(10, prec);

  long double rnorm = floorl(norm * mult + 0.5L) / mult;
  pos += s21_sprintf_itoa_custom((long long)rnorm, buffer + pos, 10, false);
  buffer[pos++] = '.';
  long long frac_int = (long long)roundl((rnorm - (long long)rnorm) * mult);
  char frac_buf[64] = {0};
  int frac_len = s21_sprintf_utoa_custom(frac_int, frac_buf, 10, false);
  while (frac_len < prec) {
    buffer[pos++] = '0';
    prec--;
  }
  s21_memcpy(buffer + pos, frac_buf, frac_len);
  pos += frac_len;
  s21_sprintf_format_exponent_part(buffer, &exponent, uppercase, &pos);
  pos += s21_sprintf_itoa_custom(exponent, buffer + pos, 10, false);
  buffer[pos] = '\0';
  return pos;
}

int s21_sprintf_format_pointer(va_list args, char *buffer) {
  void *ptr = va_arg(args, void *);
  unsigned long long addr = (unsigned long long)ptr;
  int pos = 0;
  buffer[pos++] = '0';
  buffer[pos++] = 'x';
  pos += s21_sprintf_utoa_custom(addr, buffer + pos, 16, false);
  return pos;
}

void s21_sprintf_write_padding(char **dest, int padding, char pad_char,
                               int *written) {
  for (int i = 0; i < padding; i++) {
    **dest = pad_char;
    (*dest)++;
    (*written)++;
  }
}