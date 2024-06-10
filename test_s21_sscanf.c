#include <check.h>
#include "s21_string.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
// Тест для чтения целого числа
START_TEST(test_sscanf_int) {
    int value;
    s21_sscanf("123", "%d", &value);
    ck_assert_int_eq(value, 123);
}
END_TEST

// Тест для чтения строки
START_TEST(test_sscanf_string) {
    char str[20];
    s21_sscanf("hello world", "%s", str);
    ck_assert_str_eq(str, "hello");
}
END_TEST

// Тест для чтения числа с плавающей точкой
START_TEST(test_sscanf_float) {
    float value;
    s21_sscanf("123.456", "%f", &value);
    ck_assert_float_eq_tol(value, 123.456, 0.001);
}
END_TEST

// Тест для чтения символа
START_TEST(test_sscanf_char) {
    char ch;
    s21_sscanf("a", "%c", &ch);
    ck_assert_int_eq(ch, 'a');
}
END_TEST

// Создание тестового набора для s21_sscanf
Suite *s21_sscanf_suite(void) {
    Suite *s;
    TCase *tc_core;

    s = suite_create("s21_sscanf");

    tc_core = tcase_create("Core");

    tcase_add_test(tc_core, test_sscanf_int);
    tcase_add_test(tc_core, test_sscanf_string);
    tcase_add_test(tc_core, test_sscanf_float);
    tcase_add_test(tc_core, test_sscanf_char);
    suite_add_tcase(s, tc_core);

    return s;
}

int main(void) {
    int number_failed;
    Suite *s;
    SRunner *sr;

    s = s21_sscanf_suite();
    sr = srunner_create(s);

    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
