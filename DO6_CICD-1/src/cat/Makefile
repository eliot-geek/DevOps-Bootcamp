CC = gcc
CFLAGS = -Wall -Werror -Wextra 
#FSAN = -fsanitize=address

all : s21_cat

s21_cat : s21_cat.o
	$(CC) $(CFLAGS) s21_cat.o -o s21_cat

s21_cat.o : s21_cat.c s21_cat.h
	$(CC) $(CFLAGS) -c s21_cat.c

clang: 
	clang-format -i *.c *.h

cppcheck:
	cppcheck --enable=all --suppress=missingIncludeSystem *.c *.h

clean:
	rm -rf *.o

fclean: 
	rm -rf s21_cat

rebuild:
	make clean
	make fclean
	make all

