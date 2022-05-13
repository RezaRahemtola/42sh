##
## EPITECH PROJECT, 2021
## libmy
## File description:
## Makefile
##

SRC_DIR =	src/

SRC		=	array/my_arrays.c \
			list/my_list_add.c \
			list/my_list_operations.c \
			list/my_list_remove.c \
			math/my_getnbr.c \
            math/my_is_number.c \
			string/my_revstr.c \
			string/my_str_checks.c \
			string/my_str_contains.c \
			string/my_str_starts.c \
			string/my_strrep.c \
			string/my_strsplit.c \
			string/my_strsplit_many.c \
			string/my_substr.c \
			my_free.c

OBJ		=	$(addprefix $(SRC_DIR), $(SRC:.c=.o))

NAME	=	libmy.a

INC		=	include/

AR		=	ar rc
CC		=	gcc
CFLAGS	=	-Wall -Wextra -Wpedantic
CPPFLAGS =	-iquote $(INC)

all: $(NAME)

$(NAME): $(OBJ)
	$(AR) $(NAME) $(OBJ)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

install: fclean
	$(RM) -r .git/
	$(RM) -r .idea/
	$(RM) .gitignore

re:     fclean all

.PHONY: all clean fclean install re
