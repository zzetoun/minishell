/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_mini.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzetoun <zzetoun@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 14:23:53 by zzetoun           #+#    #+#             */
/*   Updated: 2025/04/21 19:45:55 by zzetoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_MINI_H
# define STRUCT_MINI_H

# include "minishell.h"

typedef struct s_token
{
	char			*str;
	char			*str_backup;
	int				var_exists;
	int				type;
	int				status;
	int				join;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

typedef struct s_envp
{
	char			*str;
	size_t			idx;
	struct s_envp	*next;
}	t_envp;

typedef struct s_env_info
{
	t_envp		*head;
	t_envp		*tail;
	size_t		size;
}	t_env_info;

typedef struct s_io_fds
{
	char	*infile;
	char	*outfile;
	char	*heredoc_delimiter;
	int		heredoc_quotes;
	int		fd_in;
	int		fd_out;
	int		stdin_backup;
	int		stdout_backup;
}	t_io_fds;

typedef struct s_command
{
	char				*command;
	char				*path;
	char				**args;
	int					pipe_output;
	int					*pipe_fd;
	t_io_fds			*io_fds;
	struct s_command	*next;
	struct s_command	*prev;
}	t_command;

typedef struct s_data
{
	int			interactive;
	t_token		*token;
	char		*user_input;
	char		**env;
	char		*working_dir;
	char		*old_working_dir;
	t_command	*cmd;
	pid_t		pid;
}	t_data;

enum e_token_types
{
	SPACES = 1,
	WORD,
	VAR,
	PIPE,
	INPUT,
	TRUNC,
	HEREDOC,
	APPEND,
	END
};

enum e_quoting_status
{
	DEFAULT,
	SQUOTE,
	DQUOTE
};

#endif