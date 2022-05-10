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

LIBS		=	my

BINARY			=	42sh
TEST_BINARY		=	$(BINARY).test
DEBUG_BINARY	=	$(BINARY).debug

HEADERS_DIRS 	=	include/ \
					$(LIBS:%=lib/%/include/)

CFLAGS		=	-Wall -Wextra
CPPFLAGS	=	$(HEADERS_DIRS:%=-iquote %)
LDLIBS		=	$(addprefix -l, $(LIBS))
LDFLAGS		=	$(LIBS:%=-L lib/%/)

VG_FLAGS	=	--leak-check=full --track-origins=yes --show-leak-kinds=all \
				--error-limit=no

CC			=	gcc
VG			=	valgrind $(VG_FLAGS)

all:	$(BINARY)

$(BINARY):	$(OBJ)
			$(MAKE) -C lib/my
			$(CC) -o $(BINARY) $(OBJ) $(LDFLAGS) $(LDLIBS)

$(TEST_BINARY): LDLIBS	+=	-lcriterion -lgcov
$(TEST_BINARY): CFLAGS	+=	-ftest-coverage -fprofile-arcs
$(TEST_BINARY):	$(TEST_OBJ)
			$(MAKE) -C lib/my
			$(CC) -o $(TEST_BINARY) $(TEST_OBJ) $(LDFLAGS) $(LDLIBS)

$(DEBUG_BINARY):	CFLAGS	+=	-g
$(DEBUG_BINARY):	$(OBJ)
			$(MAKE) -C lib/my
			$(CC) -o $(DEBUG_BINARY) $(OBJ) $(LDFLAGS) $(LDLIBS)

clean:
			$(RM) $(OBJ)

fclean:	clean
			$(RM) $(BINARY) $(TEST_BINARY) $(DEBUG_BINARY)

clean_coverage:	fclean
			@find \( -name '*.gcno' -o -name '*.gcda' \) -delete

re:	fclean all

debug_run:	fclean $(DEBUG_BINARY)
			$(VG) ./$(DEBUG_BINARY) $(ARGS)

tests_run:
			$(MAKE) unit_tests
			$(MAKE) func_tests

unit_tests:	clean_coverage $(TEST_BINARY)
			./$(TEST_BINARY)

func_tests:	re
			@python3 -m pip install termcolor > /dev/null
			python3 tests/tester.py -adc

.PHONY:	all	clean fclean clean_coverage re debug_run tests_run unit_tests \
		func_tests
