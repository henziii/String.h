all: test

test: s21_string.a s21_test.o
	gcc  -Wall -Wextra -Werror -o test s21_string.a s21_test.o -lcheck -lm
	rm -f *.o

s21_string.a: s21_string.o utl.o
	ar rc s21_string.a s21_string.o utl.o
	ranlib s21_string.a

s21_string.o: s21_string.c
	gcc -Wall -Wextra -c s21_string.c -lm

s21_test.o: s21_test.c
	gcc -Wall -Wextra -c s21_test.c -lm

utl.o: utl.c
	gcc -Wall -Wextra -c utl.c -lm

clang:
	clang-format -n *.c *.h

brew_lcov:
	curl -fsSL https://rawgit.com/kube/42homebrew/master/install.sh | zsh
	brew install lcov

clean: 
	rm -rf test *.o *.a *gcda report *gcno *info

rebuild: clean all

gcov_report: clean s21_test.o
	gcc -o test s21_test.o --coverage s21_string.c utl.c -lcheck -lm
	./test
	lcov -t "a.out" -o test.info -c -d .
	genhtml -o report test.info
