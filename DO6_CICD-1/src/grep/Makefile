CC = gcc
CFLAGS = -Wall -Werror -Wextra 
EXEC=s21_grep
#FSAN = -fsanitize=address

all : s21_grep
	@rm *.o
s21_grep : s21_grep.o
	$(CC) $(CFLAGS) s21_grep.o -o $(EXEC)

s21_grep.o : s21_grep.c s21_grep.h
	$(CC) $(CFLAGS) -c s21_grep.c

clang: 
	clang-format -i *.c *.h

cppcheck:
	cppcheck --enable=all --suppress=missingIncludeSystem *.c *.h

clean:
	rm -rf *.o

fclean: 
	rm -rf $(EXEC)

rebuild:
	make clean
	make fclean
	make all

.PHONY:	all clean fclean rebuild