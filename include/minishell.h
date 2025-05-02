/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzetoun <zzetoun@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 17:02:27 by zzetoun           #+#    #+#             */
/*   Updated: 2025/04/30 21:38:35 by zzetoun          ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdarg.h>
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
# include "../srcs/env/env.h"
# include "../srcs/parser/parser.h"
# include "../srcs/signal/signal.h"
# include "../srcs/cleanup/freedom.h"
# include "../srcs/error/controllers.h"
# include "../srcs/utils/mini_utils.h"
# include "../srcs/utils/libft/libft.h"

# define PROMPT "\001\e[44m\002*** \001\e[0m\e[96m\002 Minishell>$ \001\e[0m\002"
# define EARGS "ERROR: invalid arguments"
# define NOACC "ERROR: permission denied"
# define EUNKN "ERROR: unknown error"
# define PATHE "ERROR: Commands Path"
# define ARGUE "ERROR: Commands error"
# define ARGEER01 "ERROR: use ./minishell"
# define ARGEER02 "ERROR: use ./minishell -c \"input line\""
# define ENVERRO "ERROR: Could not initialize environment"
# define WDWRROR "ERROR: Could not initialize working directories"
# define MINIEXP "not a valid identifier"
# define CMD_NOT_FOUND 127

//extern int	final_exit_code;

void    setup_minishell(t_token *token);

#endif