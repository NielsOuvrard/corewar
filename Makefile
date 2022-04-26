##
## EPITECH PROJECT, 2021
## Makefile
## File description:
## un makefile de qualité spécial lem-in
##

SRC = 	src/*.c

BINARY = corewar_test
# corewar/corewar

LIB = -I./include/ -L./lib/my/ -lm -lmy

all:
		@cp ./lib/my/my.h include/my.h
		@gcc -c lib/my/*.c
		@ar rc lib/my/libmy.a *.o
		@cp ./lib/my/libmy.a lib/libmy.a
		@gcc -o $(BINARY) -g $(SRC) $(LIB) -g3
		@chmod 777 $(BINARY)
		@make clean

clean:
		rm -f *.o
		rm -f *.gcno
		rm -f *.gcda
		rm -f tests_bin

fclean: clean
		rm lib/my/libmy.a
		rm lib/libmy.a
		rm $(BINARY)

re:	fclean all

auteur:
		@echo $(USER) is the best

push:
		@git add .
		@git status
		@git commit -m "push automatique"
		@git push

vg_del:
		rm vgcore.*

fm_push:
		make fclean
		make push

# tests_run:
# 		cp ./lib/my/my.h include/my.h
# 		gcc -c lib/my/*.c
# 		ar rc lib/my/libmy.a *.o
# 		cp ./lib/my/libmy.a lib/libmy.a
# 		gcc -o tests_bin -g tests/*.c $(SRC) $(LIB) -g3 -lcriterion --coverage
# 		chmod 777 tests_bin
# 		./tests_bin < input
# 		make clean

.PHONY: all clean fclean re push vg_del fm_push #tests_run