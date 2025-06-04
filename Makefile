# **************************************************************************** #
#                                  VARIABLES                                   #
# **************************************************************************** #

NAME        = minishell

# libft
LIBFT_DIR   = srcs/utils/libft
LIBFT_LIB   = $(LIBFT_DIR)/libft.a

# Directories
SRCDIR      = srcs
INCDIR      = include

# Automatically find all .c source files recursively in $(SRCDIR)
SRC         = $(shell find $(SRCDIR) -type f -name "*.c")
OBJ         = $(SRC:.c=.o)

# Compiler and flags
CC          = cc -g3 -fsanitize=address,undefined -O0 -fno-omit-frame-pointer -fno-optimize-sibling-calls
CFLAGS      = -Wall -Wextra -Werror -I$(INCDIR) -I/opt/vagrant/embedded/include
LDFLAGS     = -L/opt/vagrant/embedded/lib/ -lreadline -lhistory

# **************************************************************************** #
#                                  RULES                                       #
# **************************************************************************** #

.PHONY: all libft clean fclean re

all: libft $(NAME)

# First, build the libft library by invoking its own Makefile
libft:
	@$(MAKE) --no-print-directory -C $(LIBFT_DIR)

# Now build your shell, linking in libft.a
$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LDFLAGS) $(LIBFT_LIB) -o $(NAME)

# Pattern rule to compile .c files to .o object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -f $(OBJ)
	@$(MAKE) --no-print-directory -C $(LIBFT_DIR) clean

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) --no-print-directory -C $(LIBFT_DIR) fclean

re: fclean all
