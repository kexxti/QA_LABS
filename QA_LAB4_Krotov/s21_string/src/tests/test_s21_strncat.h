#ifndef TEST_S21_STRNCAT_H
#define TEST_S21_STRNCAT_H

#include <check.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Suite *s21_strncat_suite(void);
void reset_buffers(char *dest_s21, char *dest_std, const char *initial_dest,
                   const char **src_ptr, const char *src_str);

#endif
