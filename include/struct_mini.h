/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_mini.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzetoun <zzetoun@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 18:28:29 by zzetoun           #+#    #+#             */
/*   Updated: 2025/05/07 18:28:29 by zzetoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_MINI_H
# define STRUCT_MINI_H

# include "minishell.h"

typedef struct s_envp
{
	char			*key;
	char			*value;
	char			*str;
	size_t			idx;
	struct s_envp	*next;
}	t_envp;

typedef struct s_env_info
{
	t_envp		*head;
	size_t		size;
}	t_env_info;

typedef struct s_io_fds
{
	char	*infile;
	char	*outfile;
	char 	*append_file;
	char	*heredoc_delimiter;
	bool	heredoc_quotes;
	int		fd_in;
	int		fd_out;
	int		stdin_backup;
	int		stdout_backup;
	int		heredoc_pipe[2];
}	t_io_fds;

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

typedef struct s_command
{
    enum e_token_types  token_type;
	char				*command;
	char				*path;
	char				**args;
	bool				pipe_output;
	int					*pipe_fd;
	t_io_fds			*io_fds;
	struct s_command	*next;
	struct s_command	*prev;
}	t_command;

typedef struct s_data
{
	bool		interactive;
	t_env_info	*env;
	char		*user_input;
	char		*working_dir;
	char		*old_working_dir;
	t_command	*cmd;
	pid_t		pid;
}	t_data;

enum e_quoting_status
{
	DEFAULT,
	SQUOTE,
	DQUOTE
};

#endif
