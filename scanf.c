#include <stdio.h>
#include <stdarg.h>
#include <ctype.h>
#include <stdlib.h>
#include "s21_scanff.h"

int tipeiint(const char **s, void *p, int is_short, int is_long, int is_long_long) {
    int count = 0;
    if (is_short) {
        short *sp = (short *)p;
        *sp = 0;
        while (isdigit(**s)) {
            *sp = *sp * 10 + (**s - '0');
            (*s)++;
            count++;
        }
    } else if (is_long == 1) {
        long *lp = (long *)p;
        *lp = 0;
        while (isdigit(**s)) {
            *lp = *lp * 10 + (**s - '0');
            (*s)++;
            count++;
        }
    } else if (is_long == 2) {
        long long *llp = (long long *)p;
        *llp = 0;
        while (isdigit(**s)) {
            *llp = *llp * 10 + (**s - '0');
            (*s)++;
            count++;
        }
    } else {
        int *ip = (int *)p;
        *ip = 0;
        while (isdigit(**s)) {
            *ip = *ip * 10 + (**s - '0');
            (*s)++;
            count++;
        }
    }
    return count;
}

int withsp(const char **s, void *p, int width, int is_short, int is_long, int is_long_long) {
    int count = 0;
    while (isdigit(**s) && count < width) {
        count++;
        switch (is_short + is_long * 2 + is_long_long * 4) {
            case 1: {
                short *sp = (short *)p;
                *sp = *sp * 10 + (**s - '0');
                break;
            }
            case 2: {
                long *lp = (long *)p;
                *lp = *lp * 10 + (**s - '0');
                break;
            }
            case 4: {
                long long *llp = (long long *)p;
                *llp = *llp * 10 + (**s - '0');
                break;
            }
            default: {
                int *ip = (int *)p;
                *ip = *ip * 10 + (**s - '0');
                break;
            }
        }
        (*s)++;
    }
    return count;
}

int my_sscanf(const char *str, const char *format, ...) {
    va_list args;
    va_start(args, format);
    int count = 0;
    int width = 0;
    const char *s = str;
    const char *f = format;
    int ring = 0;

    while (*f != '\0') {
        while (isspace(*f)) {
            f++;
        }

        if (*f == '%') {
            f++;
            int is_long = 0;
            int is_short = 0;

            if (isdigit(*f)) {
                width = atoi(f);
                while (isdigit(*f)) {
                    f++;
                }
            }
            if (*f == 'h') {
                is_short = 1;
                f++;
            } else if (*f == 'l') {
                is_long = 1;
                f++;
            } else if (*f == 'L') {
                is_long = 2;
                f++;
            }

            switch (*f) {
                case 'd': {
                    void *p = va_arg(args, void *);
                    if (width) {
                        count += withsp(&s, p, width, is_short, is_long, is_long_long);
                    } else {
                        count += tipeiint(&s, p, is_short, is_long, is_long_long);
                    }
                    break;
                }
                // Add cases for other format specifiers
                default:
                    break;
            }
            f++;
        } else {
            if (*s == *f) {
                s++;
                f++;
            } else {
                break;
            }
        }
    }

    va_end(args);
    return count;
}