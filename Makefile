##
## EPITECH PROJECT, 2022
## 42sh
## File description:
## Makefile
##

BUILTIN_DIR	=	builtin
BUILTIN_SRC	=	builtin.c \
				directories.c \
				home.c \
				silent.c \
				silent_dirs.c

COMMAND_DIR	=	command
COMMAND_SRC	=	errors.c \
				execution.c \
				executor.c \
				input.c \
				output.c \
				parsing.c \
				paths.c \
				redirections.c \
				signal.c

REDIRECTION_DIR	=	redirection
REDIRECTION_SRC	=	files.c \
					pipes.c

UTIL_DIR	=	util
UTIL_SRC	=	lists.c \
				splitter.c \
				strings.c

VARENV_DIR	=	varenv
VARENV_SRC	=	varenv.c \
				variables.c \
				environment.c

BASE_DIR	= 	src
BASE_SRC	=	minishell.c \
				$(addprefix $(BUILTIN_DIR)/, $(BUILTIN_SRC)) \
				$(addprefix $(COMMAND_DIR)/, $(COMMAND_SRC)) \
				$(addprefix $(REDIRECTION_DIR)/, $(REDIRECTION_SRC)) \
				$(addprefix $(UTIL_DIR)/, $(UTIL_SRC)) \
				$(addprefix $(VARENV_DIR)/, $(VARENV_SRC))

TESTS_DIR	=	tests
TESTS_SRC	=	test_minishell.c \
				test_builtin.c \
				test_redirections.c

MAIN		=	main.c

SRC			=	$(addprefix $(BASE_DIR)/, $(BASE_SRC)) \
				$(addprefix $(BASE_DIR)/, $(MAIN))

TEST		=	$(addprefix $(BASE_DIR)/, $(BASE_SRC))\
				$(addprefix $(TESTS_DIR)/, $(TESTS_SRC))

OBJ			=	$(SRC:.c=.o)
TEST_OBJ	=	$(TEST:.c=.o)

BINARY			=	42sh
TEST_BINARY		=	$(BINARY).test

INC			=	include/
LIBINC		=	lib/my/include/

TEST_NAME	=	unit_tests

CC			=	gcc
CFLAGS		=	-Wall -Wextra
CPPFLAGS	=	-iquote $(INC) -iquote $(LIBINC)
LDLIBS		=	-lmy
LDFLAGS		=	-L lib/my/
ALLFLAGS	=	$(CPPFLAGS) $(CFLAGS) $(LDFLAGS) $(LDLIBS)

all: 		$(BINARY)

$(BINARY):	$(OBJ)
			$(MAKE) -C lib/my
			$(CC) -o $(BINARY) $(OBJ) $(LDFLAGS) $(LDLIBS)

$(TEST_BINARY): LDLIBS += -lcriterion -lgcov
$(TEST_BINARY): CFLAGS += -ftest-coverage -fprofile-arcs
$(TEST_BINARY):	$(TEST_OBJ)
				$(MAKE) -C lib/my
				$(CC) -o $(TEST_BINARY) $(TEST_OBJ) $(LDFLAGS) $(LDLIBS)

clean:
			$(RM) $(OBJ)

fclean:		clean
			$(RM) $(BINARY) $(TEST_BINARY)

re:			fclean all

tests_run:	$(TEST_BINARY)
			./$(TEST_BINARY)

tests_func: all
			@python3 -m pip install termcolor > /dev/null
			python3 tests/tester.py -adc

.PHONY: all clean fclean re tests_run
