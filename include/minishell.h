/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzetoun <zzetoun@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 17:02:27 by zzetoun           #+#    #+#             */
/*   Updated: 2025/04/09 19:00:54 by zzetoun          ###   ########.fr       */
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
# include <readline/readline.h>
# include <readline/history.h>
# include "../srcs/io/io.h"
# include "../srcs/cmd/cmd.h"
# include "../srcs/exc/exc.h"
# include "../srcs/error/controllers.h"
# include "../srcs/parser/parser.h"
# include "../srcs/signal/signal.h"
# include "../srcs/memory/mem_utils.h"
# include "../srcs/memory/freedom.h"
# include "../srcs/str_utils/utils/str_uti.h"
# include "../srcs/str_utils/get_next_line/get_next_line.h"


# define EARGS "error: invalid arguments"
# define NOACC "error: permission denied"
# define EUNKN "error: unknown error"
# define PATHE "error: Commands Path"
# define ARGUE "error: Commands error"
# define ECFND 127
# define EPERM 126

typedef struct s_token
{
	char	*str;
	char	**full_str;
}	t_token;


void 	setup_minishell(t_token *token);

#endif