# **************************************************************************** #
#                                  VARIABLES                                   #
# **************************************************************************** #

NAME      = minishell

# Directories
SRCDIR    = srcs
INCDIR    = include

# Automatically find all .c source files recursively in $(SRCDIR)
SRC       = $(shell find $(SRCDIR) -type f -name "*.c")
OBJ       = $(SRC:.c=.o)

# Compiler and flags
CC        = gcc
CFLAGS    = -Wall -Wextra -Werror -I$(INCDIR) -I/opt/vagrant/embedded/include -g3 -fsanitize=address

# **************************************************************************** #
#                                  RULES                                       #
# **************************************************************************** #

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -L/opt/vagrant/embedded/lib/ -lreadline -lhistory -o $(NAME)

# Pattern rule to compile .c files to .o object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -f $(OBJ)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
