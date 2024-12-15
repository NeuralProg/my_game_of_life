##
## EPITECH PROJECT, 2024
## B-MUL-100-MLH-1-1-my_game_of_life-yann.toison-chabane
## File description:
## Makefile
##

SRC	=	src/project/main.c\
		src/project/init_structs.c\
		src/project/init_interface.c\
		src/basics/display_help.c\
		src/basics/my_int_to_str.c\
		src/basics/my_puterr.c\
		src/basics/my_str_concatenate.c\
		src/basics/random_int.c\
		src/basics/my_int_len.c\
		src/basics/my_strlen.c\

NAME	=	my_game_of_life

OBJ	=	$(SRC:.c=.o)

CSFML_F += -lcsfml-graphics -lcsfml-system -lcsfml-audio -lcsfml-window

MATH_F += -lm

LIBFLAGS += $(CSFML_F) $(MATH_F)

CFLAGS += -I include/ -g

all:	$(NAME)									#all rule

$(NAME): $(OBJ)
	gcc $(CFLAGS) -o $(NAME) $(SRC) $(LIBFLAGS)

clean:											#clean rule
	rm -f *.o

fclean:		clean								#fclean rule
	rm -f $(OBJ)
	rm -f *.a
	rm -f $(NAME)

re:	fclean $(NAME)								#re rule
