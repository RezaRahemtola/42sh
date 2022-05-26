##
## EPITECH PROJECT, 2022
## 42sh
## File description:
## Makefile
##

BUILTIN_DIR	=	builtin
BUILTIN_SRC	=	alias.c \
				builtin.c \
				directories.c \
				history.c \
				home.c \
				localenv.c \
				silent.c \
				silent_dirs.c \
				unalias.c

COMMAND_DIR	=	command
COMMAND_SRC	=	errors.c \
				execution.c \
				executor.c \
				input.c \
				logical.c \
				output.c \
				parsing.c \
				paths.c \
				redirections.c \
				signal.c

REDIRECTION_DIR	=	redirection
REDIRECTION_SRC	=	files.c \
					pipes.c

UTILS_DIR	=	utils
UTILS_SRC	=	lists.c \
				logical.c \
				redirections.c \
				replacements.c \
				strings.c \
				history/history.c \
				history/interact.c \
				history/substitutions.c \
				history/add.c \
				history/save.c

ENV_DIR	=	environment
ENV_SRC	=	environment.c \
			environment_utils.c \
			variables.c \
			local/localenv_utils.c \
			local/localenv.c \
			local/localenv_variables.c

BASE_DIR	= 	src
BASE_SRC	=	shell.c \
				$(addprefix $(BUILTIN_DIR)/, $(BUILTIN_SRC)) \
				$(addprefix $(COMMAND_DIR)/, $(COMMAND_SRC)) \
				$(addprefix $(REDIRECTION_DIR)/, $(REDIRECTION_SRC)) \
				$(addprefix $(UTILS_DIR)/, $(UTILS_SRC)) \
				$(addprefix $(ENV_DIR)/, $(ENV_SRC))

TESTS_DIR	=	tests/src
TESTS_SRC	=	test_shell.c \
				builtin/tests_alias.c \
				builtin/tests_cd.c \
				builtin/tests_env.c \
				builtin/tests_exit.c \
				separators/tests_and.c \
				separators/tests_or.c \
				separators/tests_semicolon.c \
				test_builtin.c \
				test_redirections.c

MAIN		=	main.c

SRC			=	$(addprefix $(BASE_DIR)/, $(BASE_SRC)) \
				$(addprefix $(BASE_DIR)/, $(MAIN))

TEST		=	$(addprefix $(BASE_DIR)/, $(BASE_SRC)) \
				$(addprefix $(TESTS_DIR)/, $(TESTS_SRC))

OBJ			=	$(SRC:.c=.o)
TEST_OBJ	=	$(TEST:.c=.o)

LIBS			=	my
LIB_DIRS		=	$(addprefix lib/, $(LIBS))

BINARY			=	42sh
TEST_BINARY		=	$(BINARY).test
DEBUG_BINARY	=	$(BINARY).debug

HEADERS_DIRS 	=	include/ \
					$(LIB_DIRS:%=%/include/)

CFLAGS		=	-Wall -Wextra
CPPFLAGS	=	$(HEADERS_DIRS:%=-iquote %)
LDLIBS		=	$(addprefix -l, $(LIBS))
LDFLAGS		=	$(addprefix -L, $(LIB_DIRS))

VG_FLAGS	=	--leak-check=full --track-origins=yes --show-leak-kinds=all \
				--error-limit=no --trace-children=no

CC			=	gcc
VG			=	valgrind $(VG_FLAGS)

all:	$(BINARY)

$(BINARY):	$(OBJ)
			$(MAKE) $(LIBS)
			$(CC) -o $(BINARY) $(OBJ) $(LDFLAGS) $(LDLIBS)

$(TEST_BINARY):	LDLIBS	+=	-lcriterion -lgcov
$(TEST_BINARY):	CFLAGS	+=	-ftest-coverage -fprofile-arcs
$(TEST_BINARY):	$(TEST_OBJ)
				$(MAKE) $(LIBS)
				$(CC) -o $(TEST_BINARY) $(TEST_OBJ) $(LDFLAGS) $(LDLIBS)

$(DEBUG_BINARY):	CFLAGS	+=	-g
$(DEBUG_BINARY):	$(OBJ) $(LIBS)
					$(MAKE) $(LIBS)
					$(CC) -o $(DEBUG_BINARY) $(OBJ) $(LDFLAGS) $(LDLIBS)

$(LIBS):
		$(MAKE) -C $(@:%=lib/%)

clean:
		$(RM) $(OBJ) $(TEST_OBJ)

fclean:	clean
		$(RM) $(BINARY) $(TEST_BINARY) $(DEBUG_BINARY)

clean_coverage:	fclean
				@find \( -name '*.gcno' -o -name '*.gcda' \) -delete

re:	fclean all

debug_run:	fclean $(DEBUG_BINARY)
			$(VG) ./$(DEBUG_BINARY) $(ARGS)

tests_all:
			$(MAKE) func_tests
			$(MAKE) unit_tests
			$(MAKE) mem_checks

tests_run:
			@$(MAKE) clean_coverage > /dev/null
			@$(MAKE) $(TEST_BINARY) > /dev/null
			./$(TEST_BINARY)

func_tests:
			@$(MAKE) re > /dev/null
			@python3 -m pip install termcolor > /dev/null
			python3 tests/tester.py -adc

mem_checks:
			@$(MAKE) fclean > /dev/null
			@$(MAKE) $(DEBUG_BINARY) > /dev/null
			@python3 -m pip install termcolor > /dev/null
			python3 tests/memory_checker.py -pcd

.PHONY:	all	clean fclean clean_coverage re debug_run tests_run unit_tests \
		func_tests
