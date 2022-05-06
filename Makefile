##
## EPITECH PROJECT, 2021
## minishell2
## File description:
## Makefile
##

SRC			=	src/minishell.c \
				src/builtin/builtin.c \
				src/builtin/directories.c \
				src/builtin/home.c \
				src/builtin/silent.c \
				src/builtin/silent_dirs.c \
				src/command/errors.c \
				src/command/execution.c \
				src/command/executor.c \
				src/command/input.c \
				src/command/output.c \
				src/command/parsing.c \
				src/command/paths.c \
				src/command/redirections.c \
				src/command/signal.c \
				src/redirection/files.c \
				src/redirection/pipes.c \
				src/util/lists.c \
				src/util/pidlists.c \
				src/util/splitter.c \
				src/util/strings.c \
				src/varenv/environment.c \
				src/varenv/varenv.c \
				src/varenv/variables.c

MAIN		=	src/main.c

OBJ			=	$(SRC:.c=.o) \
				$(MAIN:.c=.o)

NAME		=	42sh
INC			=	include/
LIBINC		=	lib/my/include/

TEST		=	unit_tests
TESTS		=	tests/test_minishell.c \
				tests/test_builtin.c \
				tests/test_redirections.c

CC			=	gcc
CPPFLAGS	=	-iquote $(INC) -iquote $(LIBINC)
CFLAGS		=	-Wall -Wextra
LDLIBS		=	-lmy
LDFLAGS		=	-L lib/my/
TESTFLAGS	=	--coverage -lcriterion
ALLFLAGS	=	$(CPPFLAGS) $(CFLAGS) $(LDFLAGS) $(LDLIBS)

all: $(NAME)

$(NAME): $(OBJ)
	make -C lib/my/
	$(CC) -o $(NAME) $(OBJ) $(LDFLAGS) $(LDLIBS)

clean:
	make clean -C lib/my/
	$(RM) $(OBJ)
	$(RM) *.gcda
	$(RM) *.gcno

fclean:	clean
	make fclean -C lib/my/
	$(RM) $(NAME)
	$(RM) $(TEST)

re:	fclean all

tests_run:
	$(RM) *.gcda
	$(RM) *.gcno
	make -C lib/my/
	$(CC) -o $(TEST) $(SRC) $(TESTS) $(TESTFLAGS) $(ALLFLAGS)
	./$(TEST)

tests_func: all
	python tests/tester.py -ad

.PHONY: all clean fclean re tests_run
