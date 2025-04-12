#*****************TESTING PARSRER MAKEFILE******************

NAME = test_parser
SRC_DIR = ${HOME}/Desktop/minishell42
SRCS = $(SRC_DIR)/test/parser/test_parser.c $(SRC_DIR)/srcs/parser/parse.c
OBJ = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	cd ../build && cc -Wall -Wextra -Werror $(OBJ) -o $(NAME)

clean:
	rm -rf $(OBJ)

fclean: clean
	cd ../build && rm -f $(NAME)
%.o: %.c
	cc -Wall -Wextra -Werror -c $< -o $@
