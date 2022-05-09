##
## EPITECH PROJECT, 2021
## libmy
## File description:
## Makefile
##

SRC		=	src/array/my_arrays.c \
			src/array/my_show_word_array.c \
			src/array/my_sort_int_array.c \
			src/array/my_sort_string_array.c \
			src/list/my_list_add.c \
			src/list/my_list_operations.c \
			src/list/my_list_remove.c \
			src/math/my_getnbr.c \
            src/math/my_getnbr_base.c \
            src/math/my_is_number.c \
        	src/math/my_nbrlen.c \
            src/math/my_number.c \
            src/math/my_operations.c \
            src/math/my_parsenbr_base.c \
            src/math/my_parsenbr_long.c \
            src/math/my_parsenbr.c \
			src/math/my_power.c \
			src/math/my_prime.c \
			src/printf/my_printf.c \
			src/printf/my_printf_bases.c \
			src/printf/my_printf_core.c \
			src/printf/my_printf_formats.c \
			src/printf/my_printf_formatter.c \
			src/printf/my_printf_info.c \
			src/printf/my_printf_numbers.c \
			src/printf/my_printf_parser.c \
			src/printf/my_printf_strings.c \
			src/string/my_revstr.c \
			src/string/my_str_cases.c \
			src/string/my_str_checks.c \
			src/string/my_str_contains.c \
			src/string/my_str_operations.c \
			src/string/my_str_starts.c \
			src/string/my_strcapitalize.c \
			src/string/my_strcat.c \
			src/string/my_strcmp.c \
			src/string/my_strcpy.c \
			src/string/my_strrep.c \
			src/string/my_strsplit.c \
			src/string/my_strsplit_many.c \
			src/string/my_strtoi.c \
			src/string/my_substr.c \
			src/my_free.c \
			src/my_print.c

OBJ		=	$(SRC:.c=.o)

NAME	=	libmy.a

INC		=	include/

AR		=	ar rc
CC		=	gcc
CFLAGS	=	-Wall -Wextra -Wpedantic
CPPFLAGS =	-iquote $(INC)
TESTFLAGS	=	--coverage -lcriterion

all: $(NAME)

$(NAME): $(OBJ)
	$(AR) $(NAME) $(OBJ)

clean:
	$(RM) $(OBJ)
	$(RM) *.gcda
	$(RM) *.gcno

fclean: clean
	$(RM) $(NAME)
	$(RM) $(TEST)

install: fclean
	$(RM) -r .git/
	$(RM) -r .idea/
	$(RM) .gitignore

re:     fclean all

.PHONY: all clean fclean install re
