#include <check.h>
#include <stdio.h>
#include <stdarg.h>
#include <ctype.h>
#include <stdlib.h>

#include "s21_scanff.h"

START_TEST(test_scan_int)
{
    int a, b, c, s, f, g;
    char str[] = "  42 100 500 ";
    int count = my_sscanf(str, "%d %d %d", &a, &b, &c);
    int counts = sscanf(str, "%d %d %d", &s, &f, &g);
    ck_assert_int_eq(count, counts);
    ck_assert_int_eq(a, s);
    ck_assert_int_eq(b, f);
    ck_assert_int_eq(c, g);
   
}
END_TEST

START_TEST(test_scan_float)
{
    float a, b;
    float s, f;
    char str[] = "3.14 2.71 ";
    int count = my_sscanf(str, "%f %f", &a, &b);
    int counts = sscanf(str, "%f %f", &s, &f);
    ck_assert_int_eq(count, counts);
    ck_assert_float_eq_tol(a, s, 0.000001);
    ck_assert_float_eq(b, f);
}
END_TEST

START_TEST(test_scan_int_width)
{
    int a, b, c, s, f, g;
    char str[] = "  42 100 500 ";
    int count = my_sscanf(str, "%2d %2d %d", &a, &b, &c);
    int counts = sscanf(str, "%2d %2d %d", &s, &f, &g);
    ck_assert_int_eq(count, counts);
    ck_assert_int_eq(a, s);
    ck_assert_int_eq(b, f);
    ck_assert_int_eq(c, g);
}
END_TEST

START_TEST(test_scan_float_width)
{
    float a, b, s, f;
    char str[] = "3.14 2.71 ";
    int count = my_sscanf(str, "%2f %3f", &a, &b);
    int counts = sscanf(str, "%2f %3f", &s, &f);
    ck_assert_int_eq(count, counts);
    ck_assert_float_eq(a, s);
    ck_assert_float_eq(b, f);
}
END_TEST

START_TEST(test_scan_long)
{
    long a, s;
   long long b, f;
    char str[] = "12345 678908989898978";
    int count = my_sscanf(str, "%ld %Ld", &a, &b);
    int counts = sscanf(str, "%ld %Ld", &s, &f);
    ck_assert_int_eq(count, counts);
    ck_assert_int_eq(a, s);
    ck_assert_int_eq(b, f);
}
END_TEST

START_TEST(test_scan_short)
{
    short a, s;
    char str[] = "32767";
    int count = my_sscanf(str, "%hd", &a);
    int counts = sscanf(str, "%hd", &s);
    ck_assert_int_eq(count, counts);
    ck_assert_int_eq(a, s);
}
END_TEST

START_TEST(test_scan_char)
{
    char a, s;
    char str[] = "help";
    int count = my_sscanf(str, "%c", &a);
    int counts = sscanf(str, "%c", &s);
    
    ck_assert_int_eq(count, counts);
    ck_assert_int_eq(a, s);
}
END_TEST

START_TEST(test_scan_char_str)
{
    char a[20] = "0"; 
    char s[20] = "0"; 
    char str[] = "help";
  
    int count = my_sscanf(str, "%s", a);
   
    int counts = sscanf(str, "%s", s);
   
    ck_assert_int_eq(count, counts);
    ck_assert_str_eq(a, s);
   
       
}
END_TEST
int main(void)
{
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


    suite_add_tcase(suite, tcase);

    SRunner *runner = srunner_create(suite);
    srunner_run_all(runner, CK_NORMAL);
    int number_failed = srunner_ntests_failed(runner);
    srunner_free(runner);

    return (number_failed == 0) ? 0 : 1;
}
