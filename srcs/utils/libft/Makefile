# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: zzetoun <zzetoun@student.42abudhabi.ae>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/03 17:24:30 by zzetoun           #+#    #+#              #
#    Updated: 2025/06/07 20:17:24 by zzetoun          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


SRCS	= ft_array_len.c	\
		  ft_bzero.c		\
		  ft_calloc.c		\
		  ft_strdup.c		\
		  ft_memset.c		\
		  ft_memchr.c		\
		  ft_memcpy.c		\
		  ft_memmove.c		\
		  ft_memcmp.c		\
		  ft_strncmp.c		\
		  ft_strlen.c		\
		  ft_strlcpy.c		\
		  ft_strlcat.c		\
		  ft_strchr.c		\
		  ft_strnstr.c		\
		  ft_strrchr.c		\
		  ft_atoi.c			\
		  ft_isalpha.c		\
		  ft_isupper.c		\
		  ft_toupper.c		\
		  ft_islower.c		\
		  ft_tolower.c		\
		  ft_isdigit.c		\
		  ft_isalnum.c		\
		  ft_isascii.c		\
		  ft_isprint.c		\
		  ft_isspace.c		\
		  ft_strjoin.c		\
		  ft_strjoin_free.c	\
		  ft_strtrim.c		\
		  ft_substr.c		\
		  ft_split.c		\
		  ft_str_tolower.c	\
		  ft_itoa.c			\
		  ft_putchar_fd.c	\
		  ft_putstr_fd.c	\
		  ft_putendl_fd.c	\
		  ft_putnbr_fd.c	\
		  ft_strmapi.c		\
		  ft_striteri.c		\
		  ft_darray_to_str.c

OBJS	= ${SRCS:.c=.o}

SRCS_BO	= ft_lstnew.c		\
		  ft_lstlast.c		\
		  ft_lstsize.c		\
		  ft_lstadd_front.c	\
		  ft_lstadd_back.c	\
		  ft_lstdelone.c	\
		  ft_lstclear.c		\
		  ft_lstiter.c		\
		  ft_lstmap.c

OBJS_BO	= ${SRCS_BO:.c=.o}

NAME	= libft.a
LIBC	= ar r
CC		= cc
RM		= rm -f
CFLAGS	= -Wall -Werror -Wextra

all: ${NAME}

${NAME}: ${OBJS}
	${LIBC} ${NAME} ${OBJS}

bonus: ${OBJS_BO}
	${LIBC} ${NAME} ${OBJS_BO}

%.o : %.c
	${CC} ${CFLAGS} -c $< -o $@

clean:
	${RM} ${OBJS} ${OBJS_BO}

fclean: clean
	${RM} ${NAME}

re: fclean all
