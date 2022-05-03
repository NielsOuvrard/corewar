##
## EPITECH PROJECT, 2021
## Makefile
## File description:
## un makefile de qualité spécial lem-in
##

SRC = 	src/*.c

BINARY_ASM = asm
BINARY_COR = corewar
# corewar/corewar

FLAGS = -g3 -g

LIB = -I./include/ -L./lib/my/ -lmy

all:
		@cp ./lib/my/my.h include/my.h
		@gcc -c lib/my/*.c
		@ar rc lib/my/libmy.a *.o
		@gcc -o $(BINARY_ASM)_ src_$(BINARY_ASM)/*.c $(LIB) $(LIB) $(FLAGS)
		@gcc -o $(BINARY_COR)_ src_$(BINARY_COR)/*.c $(LIB) $(LIB) $(FLAGS)
		@mv $(BINARY_ASM)_ $(BINARY_ASM)/$(BINARY_ASM)
		@mv $(BINARY_COR)_ $(BINARY_COR)/$(BINARY_COR)
		@make clean

clean:
		rm -f *.o
		rm -f *.gcno
		rm -f *.gcda

fclean: clean
		rm -f lib/my/libmy.a
		rm -f lib/libmy.a
		rm -f $(BINARY_COR)/$(BINARY_COR)
		rm -f $(BINARY_ASM)/$(BINARY_ASM)

re:	fclean all

mac_del:
		rm -Rf *.dSYM
		rm -Rf .vscode
		rm -Rf .DS_Store

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

.PHONY: all clean fclean re push vg_del fm_push mac_del #tests_run