/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzetoun <zzetoun@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 17:02:27 by zzetoun           #+#    #+#             */
/*   Updated: 2025/04/16 19:45:36 by zzetoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdarg.h>
# include <limits.h>
# include <unistd.h>
# include <string.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <stddef.h>
# include <stdint.h>
# include <signal.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "struct_mini.h"
# include "../srcs/io/io.h"
# include "../srcs/cmd/cmd.h"
# include "../srcs/exc/exc.h"
# include "../srcs/parser/parser.h"
# include "../srcs/signal/signal.h"
# include "../srcs/memory/freedom.h"
# include "../srcs/memory/mem_utils.h"
# include "../srcs/display/ft_printf.h"
# include "../srcs/error/controllers.h"
# include "../srcs/utils/libft/libft.h"
# include "../srcs/utils/str_utils/str_uti.h"
# include "../srcs/utils/str_utils/get_next_line/get_next_line.h"

# define EARGS "error: invalid arguments"
# define NOACC "error: permission denied"
# define EUNKN "error: unknown error"
# define PATHE "error: Commands Path"
# define ARGUE "error: Commands error"
# define ARGEER01 "error: use ./minishell"
# define ARGEER02 "error: use ./minishell -c \"input line\""
# define CMD_NOT_FOUND 127

extern int	final_exit_code;

void    setup_minishell(t_token *token);

#endif