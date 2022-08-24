CC+FLAGS = gcc -std=c11 -Wall -Wextra -Werror -std=c11
GCOVFLAGS = -L. --coverage -ls21_matrix
OS = $(shell uname)
ifeq ($(OS), Linux)
	CHECK_FLAGS = -lcheck -lm -pthread -lrt -lsubunit
else
	CHECK_FLAGS = -lcheck
endif

TEST_COMPILE = $(CC+FLAGS) tests.c s21_matrix.a $(CHECK_FLAGS) -L. -ls21_matrix

all: clean s21_matrix.a test

clean:
	rm -rf *.o *.g* *.info *.out report *.a *.dSYM

rebuild: clean all

test: s21_matrix.a
	$(TEST_COMPILE)
	./a.out

gcov_report: test
	rm -f *.g*
	$(CC+FLAGS) s21*.c tests.c s21_matrix.a $(CHECK_FLAGS) $(GCOVFLAGS)
	./a.out
	lcov -t a.out -o rep.info -c -d .
	genhtml -o report rep.info
	open ./report/index.html
	rm -rf *.gcda *.gcno *.info

s21_matrix.a: s21_matrix.o
	ar rcs libs21_matrix.a *.o
	rm -rf *.o
	ranlib libs21_matrix.a
	cp libs21_matrix.a s21_matrix.a
	cp libs21_matrix.a ls21_matrix.a

s21_matrix.o:
	$(CC+FLAGS) -c s21*.c

lo:
	for i in `seq 100 $(OP)`;	do ./a.out; done;

check:
	python3 ../materials/linters/cpplint.py --extensions=c *.c *.h
	make test
ifeq ($(OS), Darwin)
	CK_FORK=no leaks --atExit -- ./a.out
else
	valgrind ./a.out --leak-check=full
endif
	make clean
