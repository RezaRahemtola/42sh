##
## EPITECH PROJECT, 2022
## 42sh
## File description:
## Makefile
##

SRC_DIR		= 	src/

SRC			=	minishell.c \
				builtin/builtin.c \
				builtin/directories.c \
				builtin/home.c \
				builtin/silent.c \
				builtin/silent_dirs.c \
				command/errors.c \
				command/execution.c \
				command/executor.c \
				command/input.c \
				command/output.c \
				command/parsing.c \
				command/paths.c \
				command/redirections.c \
				command/signal.c \
				redirection/files.c \
				redirection/pipes.c \
				util/lists.c \
				util/splitter.c \
				util/strings.c \
				varenv/environment.c \
				varenv/varenv.c \
				varenv/variables.c

MAIN		=	main.c

OBJ			=	$(addprefix $(SRC_DIR), $(SRC:.c=.o)) \
				$(addprefix $(SRC_DIR), $(MAIN:.c=.o))

NAME		=	42sh
INC			=	include/
LIBINC		=	lib/my/include/

TEST_NAME	=	unit_tests
TESTED		=	$(addprefix $(SRC_DIR), $(SRC))
TESTS		=	tests/test_minishell.c \
				tests/test_builtin.c \
				tests/test_redirections.c

CC			=	gcc
CFLAGS		=	-Wall -Wextra
CPPFLAGS	=	-iquote $(INC) -iquote $(LIBINC)
LDLIBS		=	-lmy
LDFLAGS		=	-L lib/my/
TESTFLAGS	=	--coverage -lcriterion
ALLFLAGS	=	$(CPPFLAGS) $(CFLAGS) $(LDFLAGS) $(LDLIBS)

all: 		$(NAME)

$(NAME): 	$(OBJ)
			make -C lib/my/
			$(CC) -o $(NAME) $(OBJ) $(LDFLAGS) $(LDLIBS)

clean:
			make clean -C lib/my/
			$(RM) $(OBJ)
			$(RM) *.gcda
			$(RM) *.gcno

fclean:		clean
			make fclean -C lib/my/
			$(RM) $(NAME)
			$(RM) $(TEST)

re:			fclean all

tests_run:
			$(RM) *.gcda
			$(RM) *.gcno
			make -C lib/my/
			$(CC) -o $(TEST_NAME) $(TESTED) $(TESTS) $(TESTFLAGS) $(ALLFLAGS)
			./$(TEST_NAME)

tests_func: all
			@python3 -m pip install termcolor
			python3 tests/tester.py -adc

.PHONY: all clean fclean re tests_run
