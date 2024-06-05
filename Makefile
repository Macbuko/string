CC = gcc
CFLAGS = -Wall -Wextra -Werror 
LDLIBS = -lcheck -lm -lsubunit

all: test

test: test_my_sscanf.c s21_scanff.o
	$(CC) $(CFLAGS) -o test test_my_sscanf.c s21_scanff.o $(LDLIBS)

s21_scanff.o: s21_scanff.c s21_scanff.h
	$(CC) $(CFLAGS) -c s21_scanff.c

clean:
	rm -f test s21_scanff.o
