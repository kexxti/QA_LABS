#ifndef TEST_S21_MEMCHR_H
#define TEST_S21_MEMCHR_H

#include <check.h>
#include <stdio.h>
#include <string.h>

typedef struct {
  char str[27];
  char str2[27];
} TwoArrays;

TwoArrays init_struct_with_alphabet(void);
Suite *s21_memchr_suite(void);

#endif