##
## EPITECH PROJECT, 2024
## B-MUL-100-MLH-1-1-my_game_of_life-yann.toison-chabane
## File description:
## Makefile
##

SRC	=	src/project/main.c\
		src/project/init_structs.c\
		src/project/init_interface.c\
		src/project/grid_actions.c\
		src/project/calculate_next_gen.c\
		src/project/display_all.c\
		src/project/manage_events.c\
		src/project/buttons_actions.c\
		src/project/submenus_actions.c\
		src/project/key_actions.c\
		src/project/init_submenus.c\
		src/project/trigger_pop_up.c\
		src/project/is_cell_in_selection_range.c\
		src/project/calculate_mouse_pos.c\
		src/basics/display_help.c\
		src/basics/my_int_to_str.c\
		src/basics/my_puterr.c\
		src/basics/my_str_concatenate.c\
		src/basics/random_int.c\
		src/basics/my_int_len.c\
		src/basics/my_strlen.c\

NAME	=	my_game_of_life

OBJ	=	$(SRC:.c=.o)

CSFML_F += -lcsfml-graphics -lcsfml-system -lcsfml-audio -lcsfml-window		#lib flags
MATH_F += -lm
CJSON_F += -lcjson
OPENMP_F += -fopenmp

LIBFLAGS += $(CSFML_F) $(MATH_F) $(CJSON_F) $(OPENMP_F)

CFLAGS += -I include/ -I/usr/local/include

all:	$(NAME)									#all rule

$(NAME): $(OBJ)										#build rule
	gcc $(CFLAGS) -o $(NAME) $(SRC) $(LIBFLAGS)
mac_build: $(OBJ)									#build rule for Mac (gcc version 14)
	gcc-14 $(CFLAGS) -o $(NAME) $(SRC) $(LIBFLAGS)

clean:											#clean rule
	rm -f *.o

fclean:		clean								#fclean rule
	rm -f $(OBJ)
	rm -f *.a
	rm -f $(NAME)

re:	fclean $(NAME)								#re rule
re_mac: fclean mac_build						#re rule for Mac (gcc version 14)
