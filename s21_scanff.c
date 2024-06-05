#include <stdio.h>
#include <stdarg.h>
#include <ctype.h>
#include <stdlib.h>
#include "s21_scanff.h"

int my_sscanf(const char *str, const char *format, ...)
{
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
            }
            else if (*f == 'l') {
                is_long = 1;
                f++;
            }
             else if (*f == 'L') {
                is_long = 2;
                f++;
            }



            switch (*f) {
                case 'd': {
                    if (is_short) {
                        short *p = va_arg(args, short *);
                        *p = 0;
                        while (isspace(*s)) {
                            s++;
                        }
                        if (!width) {
                            while (isdigit(*s)) {
                                *p = *p * 10 + (*s - '0');
                                s++;
                            }
                        } else {
                            while (isdigit(*s) && ring < width) {
                                *p = *p * 10 + (*s - '0');
                                s++;
                                ring++;
                            }
                        }
                        count++;
                    } else if (is_long == 1) {
                        long *p = va_arg(args, long *);
                        *p = 0;
                        while (isspace(*s)) {
                            s++;
                        }
                        if (!width) {
                            while (isdigit(*s)) {
                                *p = *p * 10 + (*s - '0');
                                s++;
                            }
                        } else {
                            while (isdigit(*s) && ring < width) {
                                *p = *p * 10 + (*s - '0');
                                s++;
                                ring++;
                            }
                        }
                        count++;
                    } else if (is_long == 2) {
                        long long *p = va_arg(args, long long *);
                        *p = 0;
                        while (isspace(*s)) {
                            s++;
                        }
                        if (!width) {
                            while (isdigit(*s)) {
                                *p = *p * 10 + (*s - '0');
                                s++;
                            }
                        } else {
                            while (isdigit(*s) && ring < width) {
                                *p = *p * 10 + (*s - '0');
                                s++;
                                ring++;
                            }
                        }
                        count++;
                    } else {
                        int *p = va_arg(args, int *);
                        *p = 0;
                        while (isspace(*s)) {
                            s++;


                        }
                        if (!width) {
                            while (isdigit(*s)) {
                                *p = *p * 10 + (*s - '0');
                                s++;
                            }
                        } else {
                            while (isdigit(*s) && ring < width) {
                                *p = *p * 10 + (*s - '0');
                                s++;
                                ring++;
                            }
                        }
                        count++;
                    }
                    width = 0;
                    ring = 0;
                    break;
                }
                case 'f': {
                    if (is_long == 2) {
                        long double *p = va_arg(args, long double *);
                        *p = 0.0L;
                        int sign = 1;
                        while (isspace(*s)) {
                            s++;
                        }
                        if (*s == '-') {
                            sign = -1;
                            s++;
                        }
                        if (!width) {
                            while (isdigit(*s)) {
                                *p = *p * 10.0L + (*s - '0');
                                s++;
                            }
                            if (*s == '.') {
                                s++;
                                long double div = 10.0L;
                                while (isdigit(*s)) {
                                    *p += (*s - '0') / div;
                                    div *= 10.0L;
                                    s++;
                                }
                            }
                            *p *= sign;
                        } else {
                            while (isdigit(*s) && ring < width) {
                                *p = *p * 10.0L + (*s - '0');
                                s++;
                                ring++;
                            }
                            if (*s == '.') {
                                s++;
                                ring++;
                                long double div = 10.0L;
                                while (isdigit(*s) && ring < width) {
                                    *p += (*s - '0') / div;
                                    div *= 10.0L;
                                    s++;
                                    ring++;
                                }
                            }
                            *p *= sign;
                        }
                        count++;
                    } else {
                        float *p = va_arg(args, float *);
                        *p = 0.0f;
                        int sign = 1;
                        while (isspace(*s)) {
                            s++;
                        }
                        if (*s == '-') {
                            sign = -1;
                            s++;
                        }
                        if (!width) {
                            while (isdigit(*s)) {
                                *p = *p * 10.0f + (*s - '0');
                                s++;
                            }
                            if (*s == '.') {
                                s++;
                                float div = 10.0f;
                                while (isdigit(*s)) {
                                    *p += (*s - '0') / div;
                                    div *= 10.0f;
                                    s++;
                                }

                            }
                            *p *= sign;
                        } else {
                            while (isdigit(*s) && ring < width) {
                                *p = *p * 10.0f + (*s - '0');
                                s++;
                                ring++;
                            }
                            if (*s == '.') {
                                s++;
                                ring++;
                                float div = 10.0f;
                                while (isdigit(*s) && ring < width) {
                                    *p += (*s - '0') / div;
                                    div *= 10.0f;
                                    s++;
                                    ring++;
                                }
                            }
                            *p *= sign;
                        }
                        count++;
                    }
                    width = 0;
                    ring = 0;
                    break;
                }
    case 's': {
                    char *p = va_arg(args, char *);
                     while (isspace(*s)) {
                        s++;
                    }
                    if (!width) {
                    while (*s != ' ' && *s != '\0') {
                        *p++ = *s++;
                    }
                    *p = '\0';
                    } else {
                    while (*s != ' ' && *s != '\0' && ring < width) {
                        *p++ = *s++;
                        ring++;
                    }
                    *p = '\0';
                    }
                    count++;
                    width=0;
                    ring=0;
                    break;
                    
                }
                case 'c': {
                    char *p = va_arg(args, char *);
                     while (isspace(*s)) {
                        s++;
                    }
                    *p++ = *s++;
                    count++;
                    break;
                }

                default:
                    break;
            }
        } else if (isspace(*f)) {
            while (isspace(*s)) {
                s++;
            }
        } else if (*f == *s) {
            f++;
            s++;
        } else {
            break;
        }
        f++;
    }

    va_end(args);
    return count;
}
/*
int main()
{
    int i;
    long double f;
    char c;
    char s[100];
char a[100] = " 340 5.5                  fuck4365fdggxgnbnxjhffjghfghjfjhjggkgjkfjkfkkfjkjkj";


   int count = my_sscanf(a, "%3Ld %3Lf %Lc %5hs", &i, &f, &c, &s);
  //
//sscanf(a, "%hd %3f %c %s ", &i, &f, &c, &s);
//    printf("Count: %d\n", count);
    printf("i: %d, f: %Lf, c: %c s: %s\n", i, f, c, s);

    return 0;
}
*/