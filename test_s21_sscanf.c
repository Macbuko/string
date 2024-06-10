#include <check.h>
#include <ctype.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

#include "s21_scanf.h"

START_TEST(test_scan_int) {
  int a, b, c, s, f, g;
  char str[] = "  42 100 500 ";
  int count = s21_sscanf(str, "%d %d %d", &a, &b, &c);
  int counts = sscanf(str, "%d %d %d", &s, &f, &g);
  ck_assert_int_eq(count, counts);
  ck_assert_int_eq(a, s);
  ck_assert_int_eq(b, f);
  ck_assert_int_eq(c, g);
}
END_TEST

START_TEST(test_scan_float) {
  float a, b;
  float s, f;
  char str[] = "3.14 2.71 ";
  int count = s21_sscanf(str, "%f %f", &a, &b);
  int counts = sscanf(str, "%f %f", &s, &f);
  ck_assert_int_eq(count, counts);
  ck_assert_float_eq_tol(a, s, 0.000001);
  ck_assert_float_eq(b, f);
}
END_TEST

START_TEST(test_scan_int_width) {
  int a, b, c, s, f, g;
  char str[] = "  42 100 500 ";
  int count = s21_sscanf(str, "%d %d %d", &a, &b, &c);
  int counts = sscanf(str, "%d %d %d", &s, &f, &g);
  ck_assert_int_eq(count, counts);
  ck_assert_int_eq(a, s);
  ck_assert_int_eq(b, f);
  ck_assert_int_eq(c, g);
}
END_TEST

START_TEST(test_scan_float_width) {
  float a, b, s, f;
  char str[] = "3.14 2.71 ";
  int count = s21_sscanf(str, "%f %f", &a, &b);
  int counts = sscanf(str, "%f %f", &s, &f);
  ck_assert_int_eq(count, counts);
  ck_assert_float_eq(a, s);
  ck_assert_float_eq(b, f);
}
END_TEST

START_TEST(test_scan_long) {
  long a, s;
  long long b, f;
  char str[] = "12345 678908989898978";
  int count = s21_sscanf(str, "%ld %Ld", &a, &b);
  int counts = sscanf(str, "%ld %Ld", &s, &f);
  ck_assert_int_eq(count, counts);
  ck_assert_int_eq(a, s);
  ck_assert_int_eq(b, f);
}
END_TEST

START_TEST(test_scan_short) {
  short a, s;
  char str[] = "32767";
  int count = s21_sscanf(str, "%hd", &a);
  int counts = sscanf(str, "%hd", &s);
  ck_assert_int_eq(count, counts);
  ck_assert_int_eq(a, s);
}
END_TEST

START_TEST(test_scan_char) {
  char a, s;
  char str[] = "help";
  int count = s21_sscanf(str, "%c", &a);
  int counts = sscanf(str, "%c", &s);

  ck_assert_int_eq(count, counts);
  ck_assert_int_eq(a, s);
}
END_TEST

START_TEST(test_scan_char_str) {
  char a[20] = "0";
  char s[20] = "0";
  char str[] = "help";

  int count = s21_sscanf(str, "%s", a);

  int counts = sscanf(str, "%s", s);

  ck_assert_int_eq(count, counts);
  ck_assert_str_eq(a, s);
}
END_TEST

START_TEST(test_scan_star) {
  short a, s;
  char str[] = "32767 3";
  int count = s21_sscanf(str, "%*hd %hd", &a);
  int counts = sscanf(str, "%*d %hd", &s);
  ck_assert_int_eq(count, counts);
  ck_assert_int_eq(a, s);
}
END_TEST

START_TEST(test_scan_manysp) {
  long long i4, i2;
  long double f, f3;
  // float f1, f4;
  char c, c1;
  char s[100], s1[100];

  char a[100] = " -340   -55555.999 hello    t";

  int count = s21_sscanf(a, "%lld %Lf %s %c", &i2, &f, s, &c);

  int counts = sscanf(a, "%lld %Lf %s %c1", &i4, &f3, s1, &c1);
  ck_assert_int_eq(count, counts);
  ck_assert_int_eq(i2, i4);
  ck_assert_int_eq(c, c1);
  ck_assert_float_eq(f, f3);
  ck_assert_str_eq(s, s1);
}
END_TEST

START_TEST(test_scan_manysp1) {
  // long long i4, i2;
  long double f, f3;

  char c, c1;
  char s[100], s1[100];

  char a[100] = " -340   -55555.999 hello    t";

  int count = s21_sscanf(a, "%*lld %Lf %s %c", &f, s, &c);

  int counts = sscanf(a, "%*d %Lf %s %c1", &f3, s1, &c1);
  ck_assert_int_eq(count, counts);
  // ck_assert_int_eq(i2, i4);
  ck_assert_int_eq(c, c1);
  ck_assert_float_eq(f, f3);
  ck_assert_str_eq(s, s1);
}
END_TEST

START_TEST(test_scan_error) {
  short a, s = 8;
  char str[] = "eroor";
  int count = s21_sscanf(str, "%hd", &a);
  int counts = sscanf(str, "%hd", &s);

  ck_assert_int_eq(count, counts);
  // ck_assert_int_eq(a, s);
}
END_TEST

START_TEST(test_scan_error1) {
  short a, s, q, w;
  char str[] = " 5 eroor";
  int count = s21_sscanf(str, "%hd %hd", &q, &a);
  int counts = sscanf(str, "%hd %hd", &w, &s);
  ck_assert_int_eq(count, counts);
  // ck_assert_int_eq(a, s);
  ck_assert_int_eq(q, w);
}
END_TEST

START_TEST(test_scan_error2) {
  short a, s, q, w, e, r;
  char str[] = " 5 eroor 5";
  int count = s21_sscanf(str, "%hd %hd %hd", &q, &a, &e);
  int counts = sscanf(str, "%hd %hd %hd", &w, &s, &r);
  ck_assert_int_eq(count, counts);
  // ck_assert_int_eq(a, s);
  ck_assert_int_eq(q, w);
}
END_TEST

START_TEST(test_scan_error3) {
  float a, s, q, w, e, r;
  char str[] = " 5.5 eroor 5.5";
  int count = s21_sscanf(str, "%f %f %f", &q, &a, &e);
  int counts = sscanf(str, "%f %f %f", &w, &s, &r);
  ck_assert_int_eq(count, counts);
  // ck_assert_int_eq(a, s);
  ck_assert_int_eq(q, w);
}
END_TEST

START_TEST(test_scan_error4) {
  char a, s;
  char str[10] = "\0";
  int count = s21_sscanf(str, "%c", &a);
  int counts = sscanf(str, "%c", &s);
  ck_assert_int_eq(count, counts);
  // ck_assert_int_eq(a, s);
}
END_TEST

START_TEST(test_scan_protchent) {
  int a, s;

  char str[10] = "%5";
  int count = s21_sscanf(str, "%%%d", &a);
  int counts = sscanf(str, "%%%d", &s);
  ck_assert_int_eq(count, counts);
  ck_assert_int_eq(a, s);
}
END_TEST

START_TEST(test_scan_protchent1) {
  int a, s, q, w;

  char str[10] = " 5 %5";
  int count = s21_sscanf(str, "%d %%%d", &w, &a);
  int counts = sscanf(str, "%d %%%d", &q, &s);
  ck_assert_int_eq(count, counts);
  ck_assert_int_eq(a, s);
  ck_assert_int_eq(w, q);
}
END_TEST
START_TEST(test_scan_unsigned) {
  unsigned int a, b, c, s, f, g;
  char str[] = "  42 100 500 ";
  int count = s21_sscanf(str, "%u %u %u", &a, &b, &c);
  int counts = sscanf(str, "%u %u %u", &s, &f, &g);
  ck_assert_int_eq(count, counts);
  ck_assert_uint_eq(a, s);
  ck_assert_uint_eq(b, f);
  ck_assert_uint_eq(c, g);
}
END_TEST

START_TEST(test_scan_octal) {
  unsigned int a, b, c, s, f, g;
  char str[] = "  42 0100 0500 ";
  int count = s21_sscanf(str, "%o %o %o", &a, &b, &c);
  int counts = sscanf(str, "%o %o %o", &s, &f, &g);
  ck_assert_int_eq(count, counts);
  ck_assert_uint_eq(a, s);
  ck_assert_uint_eq(b, f);
  ck_assert_uint_eq(c, g);
}
END_TEST

START_TEST(test_scan_hex) {
  unsigned int a, b, c, s, f, g;
  char str[] = "  0x2A 0x64 0x1F4 ";
  int count = s21_sscanf(str, "%x %x %x", &a, &b, &c);
  int counts = sscanf(str, "%x %x %x", &s, &f, &g);
  ck_assert_int_eq(count, counts);
  ck_assert_uint_eq(a, s);
  ck_assert_uint_eq(b, f);
  ck_assert_uint_eq(c, g);
}
END_TEST

START_TEST(test_scan_i) {
  int a, b;
  int a1, b1;
  char str[] = "10 -20  ";
  int count = s21_sscanf(str, "%i %i", &a, &b);
  int counts = sscanf(str, "%i %i", &a1, &b1);

  ck_assert_int_eq(count, counts);
  ck_assert_int_eq(a, a1);
  ck_assert_int_eq(b, b1);
}
END_TEST

START_TEST(test_scan_i1) {
  int a, b;
  int a1, b1;
  char str[] = "  0x2A  0100 ";
  int count = s21_sscanf(str, "%i %i    ", &a, &b);
  int counts = sscanf(str, "%i %i  ", &a1, &b1);

  ck_assert_int_eq(count, counts);
  ck_assert_int_eq(a, a1);
  ck_assert_int_eq(b, b1);
}
END_TEST

START_TEST(test_scan_hex1) {
  int a, s;
  char str[] = "  0x2A";
  int count = s21_sscanf(str, "%i ", &a);
  int counts = sscanf(str, "%i ", &s);
  ck_assert_int_eq(count, counts);
  ck_assert_uint_eq(a, s);
}
END_TEST

START_TEST(test_scan_octal1) {
  int a, b, s, f;
  char str[] = "   0100 0500 ";
  int count = s21_sscanf(str, "%i %i ", &a, &b);
  int counts = sscanf(str, "%i %i ", &s, &f);
  ck_assert_int_eq(count, counts);
  ck_assert_uint_eq(a, s);
  ck_assert_uint_eq(b, f);
}
END_TEST

START_TEST(test_scan_n) {
  int a, s, q, w;
  char str[] = " 123656 1   ";
  int count = s21_sscanf(str, "%d %n ", &a, &q);
  int counts = sscanf(str, "%d %n ", &s, &w);
  ck_assert_int_eq(count, counts);
  ck_assert_uint_eq(a, s);
  ck_assert_uint_eq(q, w);
}
END_TEST

START_TEST(test_scan_p) {
  void *ptr1 = NULL, *ptr2 = NULL;
  int result1, result2;

  char input1[] = "0x123456789abcdef";
  result1 = sscanf(input1, "%p", &ptr1);
  result2 = s21_sscanf(input1, "%p", &ptr2);
  ck_assert_int_eq(result1, result2);
  ck_assert_ptr_eq(ptr1, ptr2);
}
END_TEST

START_TEST(test_scan_p1) {
  void *ptr1 = NULL, *ptr2 = NULL;
  int result1, result2;

  char input2[] = "123456789abcdef";
  ptr1 = ptr2 = NULL;
  result1 = sscanf(input2, "%p", &ptr1);
  result2 = s21_sscanf(input2, "%p", &ptr2);
  ck_assert_int_eq(result1, result2);
  ck_assert_ptr_eq(ptr1, ptr2);
}
END_TEST

int main(void) {
  Suite *suite = suite_create("my_sscanf");
  TCase *tcase = tcase_create("Core");

  tcase_add_test(tcase, test_scan_int);
  tcase_add_test(tcase, test_scan_float);
  tcase_add_test(tcase, test_scan_int_width);
  tcase_add_test(tcase, test_scan_float_width);
  tcase_add_test(tcase, test_scan_long);
  tcase_add_test(tcase, test_scan_short);
  tcase_add_test(tcase, test_scan_char);
  tcase_add_test(tcase, test_scan_char_str);
  tcase_add_test(tcase, test_scan_star);
  tcase_add_test(tcase, test_scan_manysp);
  tcase_add_test(tcase, test_scan_manysp1);
  tcase_add_test(tcase, test_scan_error);
  tcase_add_test(tcase, test_scan_error1);
  tcase_add_test(tcase, test_scan_error2);
  tcase_add_test(tcase, test_scan_error3);
  tcase_add_test(tcase, test_scan_error4);
  tcase_add_test(tcase, test_scan_protchent);
  tcase_add_test(tcase, test_scan_protchent1);
  tcase_add_test(tcase, test_scan_unsigned);
  tcase_add_test(tcase, test_scan_octal);
  tcase_add_test(tcase, test_scan_hex);
  tcase_add_test(tcase, test_scan_i);
  tcase_add_test(tcase, test_scan_i1);
  tcase_add_test(tcase, test_scan_hex1);
  tcase_add_test(tcase, test_scan_octal1);
  tcase_add_test(tcase, test_scan_n);
  tcase_add_test(tcase, test_scan_p);
  tcase_add_test(tcase, test_scan_p1);

  suite_add_tcase(suite, tcase);

  SRunner *runner = srunner_create(suite);
  srunner_run_all(runner, CK_NORMAL);
  int number_failed = srunner_ntests_failed(runner);
  srunner_free(runner);

  return (number_failed == 0) ? 0 : 1;
}
