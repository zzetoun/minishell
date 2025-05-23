/******************************************************************************/
/*																			*/
/*														:::	  ::::::::   */
/*   minishell.h										:+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: zzetoun <zzetoun@student.42abudhabi.ae>	+#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2025/04/08 17:02:27 by zzetoun		   #+#	#+#			 */
/*   Updated: 2025/04/30 21:38:35 by zzetoun		  ###   ########.fr	   */
/*																			*/
/******************************************************************************/

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdarg.h>
# include <unistd.h>
# include <string.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stddef.h>
# include <stdint.h>
# include <signal.h>
# include <errno.h>
# include <stdbool.h>
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

# define PROMPT "\001\e[44m\002* \001\e[0m\e[96m\002 Minishell>$ \001\e[0m\002"
# define PATHEN	"/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin:."
# define EARGS "ERROR: invalid arguments"
# define NOACC "ERROR: permission denied"
# define EUNKN "ERROR: unknown error"
# define PATHE "ERROR: Commands Path"
# define ARGUE "ERROR: Commands error"
# define MALLERR "an unexpected error occured"
# define PARSER01 "parsing ERROR: no command to execute!"
# define CMDERR01 "command not found"
# define CMDERR02 "is a directory"
# define ARGEER01 "ERROR: use ./minishell"
# define ARGEER02 "ERROR: use ./minishell -c \"input line\""
# define ARGERR03 "ERROR: too many arguments"
# define ARGERR04 "ERROR: numeric argument required"
# define ENVERRO "ERROR: Could not initialize environment"
# define WDERROR "ERROR: Could not initialize working directories"
# define CDERROR "cd: error retrieving current directory"
# define GETCWDE "getcwd: cannot access parent directories"
# define MINIERID "not a valid identifier"
# define MINIEROP "invalid option"
# define ALLOERRO "ERROR: allocation fails"
# define CMD_NOT_FOUND 127
# define CMD_NOT_EXECU 128

extern int	final_exit_code;

void	setup_minishell(t_token *token);

#endif
