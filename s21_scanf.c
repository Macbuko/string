#include <stdio.h>
#include <stdarg.h>
#include <ctype.h>
#include <stdlib.h>
#include "s21_scanf.h"

int star(const char **s) {
    int count = 0;
    while (isspace(**s) || **s != '\0') {
        (*s)++;

    }
      while (**s == '-' || **s == '+') {
                        (*s)++;

                         }

    while (isdigit(**s)) {
        (*s)++;

    }

    return count;
}

int star_char(const char **s) {
    int count = 0;
    while (isspace(**s)) {
        (*s)++;

    }
    if (**s != '\0') {
        (*s)++;

    }
    return count;
}

int star_str(const char **s) {
    int count = 0;
    while (isspace(**s)) {
        (*s)++;

    }
    while (**s != ' ' && **s != '\0') {
                        (*s)++;
                    }
    return count;
}


int tipe_int(const char **s, void *p, int is_short, int is_long) {
    int count = 0;
    int sing = 1;

    while (isspace(**s)) {
                        (*s)++;
                    }
    while (**s == '-' || **s == '+') {
                        if (**s == '-')
                        sing = -1;
                         if (**s == '+') {
                         }
                        (*s)++;
         }
        long long num = 0;
        while (isdigit(**s)) {
        num = num * 10 + (**s - '0');
            (*s)++;

        }
         num *= sing;
         count++;

 //printf ("%d", num);

    if (is_short) {

    short *sp = (short *)p;
    *sp = (short) num;

    } else if (is_long == 1) {
       long *lp = (long *)p;
        *lp = (long)num;

    } else if (is_long == 2) {
     long long *llp = (long long *)p;
    *llp = num;
    }

     else {
         int *ip = (int *)p;
        *ip = (int)num;

    }
    return count;
}

int tipe_float (const char **s, void *p, int is_long) {
    int count = 0;
    int sing = 1;

    while (isspace(**s)) {
                        (*s)++;
                    }
    while (**s == '-' || **s == '+') {
                        if (**s == '-')
                        sing = -1;
                         if (**s == '+') {
                         }
                        (*s)++;
                        }
                    long double num = 0;
                    while (isdigit(**s) ) {
                        num = num * 10.0f + (**s - '0');
                        (*s)++;
                            }
                            if (**s == '.') {
                                (*s)++;

                                long double div = 10.0f;
                                while (isdigit(**s)) {
                                    num += (**s - '0') / div;
                                    div *= 10.0f;
                                    (*s)++;

                                }

                            }


                        num *= sing;
                        count++;
                        if (is_long == 2) {
                            long double *lf = (long double *)p;
                                *lf = num;
                                        } else {
                                                float *fp = (float *)p;
                                                 *fp = (float)num;

}
    return count;

}


/*
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
*/
int my_sscanf(const char *str, const char *format, ...) {
    va_list args;
    va_start(args, format);
    int count = 0;
    int width = 0;
    const char *s = str;
    const char *f = format;

    while (*f != '\0') {
        while (isspace(*f)) {
            f++;
        }

        if (*f == '%') {
            f++;
            int is_long = 0;
            int is_short = 0;
            int the_star = 0;

            if (*f == '*') {
            the_star = 1;
            f++;
            }

            if (*f == 'h') {
                is_short = 1;
                f++;
            } else if (*f == 'l') {
                is_long = 1;
                f++;
                if (*f == 'l') {
                is_long ++;
                f++;
                }
            } else if (*f == 'L') {
                is_long = 2;
                f++;
            }
            switch (*f) {
            case 'd': {
                if (the_star)
                count += star(&s);
                else {
                void *p = va_arg(args, void *);
                count += tipe_int(&s, p, is_short, is_long);
                }
                break;
                }

           case 'f': {
                if (the_star)
                count += star(&s);
                else {
                void *p = va_arg(args, void *);
                count += tipe_float (&s, p, is_long);
                }
                break;
                }
            case 's': {
                if (the_star)
                count += star_str(&s);

               else  {
                char *p = va_arg(args, char *);

                    while (isspace(*s)) {
                    s++;
                    }

                        while (*s != ' ' && *s != '\0') {
                        *p++ = *s++;
                    }
                    *p = '\0';

                    count++;
                    }
                    break;

                }
        case 'c': {
                if (the_star)
                count += star_char(&s);
                  else  {
                    char *p = va_arg(args, char *);
                     while (isspace(*s)) {
                        s++;
                    }
                    *p++ = *s++;
                    count++;
                    }
                    break;
                }
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
int main()
{
    int i;
    long long i4, i2, i1;
    long double f, f3;
    float f1, f4;
    char c;
    char s[100];

char a[100] = " -340     -55555.999 hello t";




   int count = my_sscanf(a,"%lld %*Lf %s %c", &i2, &f, &s, &c);

  //
 //int counts = sscanf(a,"%lld %*Lf %s %c", &i2, &f, &s, &c);


  printf("Count: %d\n", count);
 //printf("Counts: %d\n", counts);
    printf("i: %lld %Lf %s %c\n", i2, f, s, c);
   // printf("i1: %lld %Lf\n", i1, f3);

    return 0;
}
