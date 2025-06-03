/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_mini.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzetoun <zzetoun@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 18:17:37 by zzetoun           #+#    #+#             */
/*   Updated: 2025/05/07 18:17:37 by zzetoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static bool	init_directory(t_data *data)
{
	char	buff[PATH_MAX];

	data->working_dir = ft_strdup(getcwd(buff, PATH_MAX));
	if (!data->working_dir)
		return (false);
	if (get_env(data->env, "OLDPWD"))
	{
		data->old_working_dir = ft_strdup(get_env(data->env, "OLDPWD"));
		if (!data->old_working_dir)
			return (false);
	}
	else
		data->old_working_dir = NULL;
	return (true);
}

bool	setup_mini(t_data *data, char **envp)
{
	if (ft_env_setup(data->env, envp, -1))
	{
		errmsg("Fatal", NULL, ENVERR01, EXIT_FAILURE);
		return (false);
	}
	if (!init_directory(data))
	{
		errmsg("Fatal", NULL, WDERROR, EXIT_FAILURE);
		return (false);
	}
	data->token = NULL;
	data->user_input = NULL;
	data->cmd = NULL;
	data->pid = -1;
	errno = 0;
	g_final_exit_code = 0;
	return (true);
}

void	setup_io(t_command *cmd)
{
	if (!cmd->io_fds)
	{
		cmd->io_fds = ft_calloc(1, sizeof * cmd->io_fds);
		if (!cmd->io_fds)
		{
			errmsg("malloc", NULL, MALLERR, EXIT_FAILURE);
			return ;
		}
		cmd->io_fds->infile = NULL;
		cmd->io_fds->outfile = NULL;
		cmd->io_fds->heredoc_delimiter = NULL;
		cmd->io_fds->heredoc_quotes = false;
		cmd->io_fds->fd_in = -1;
		cmd->io_fds->fd_out = -1;
		cmd->io_fds->stdin_backup = -1;
		cmd->io_fds->stdout_backup = -1;
	}
}
