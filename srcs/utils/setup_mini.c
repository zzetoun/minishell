/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_mini.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzetoun <zzetoun@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 16:01:53 by zzetoun           #+#    #+#             */
/*   Updated: 2025/04/27 18:48:40 by zzetoun          ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../include/minishell.h"

static int	init_directory(t_data *data)
{
	char	buff[PATH_MAX];

	data->working_dir = ft_strdup(getcwd(buff, PATH_MAX));
	if (!data->working_dir)
		return (0);
	if (get_env(data->env, "OLDPWD"))
	{
		data->old_working_dir = get_env(data->env, "OLDPWD");
		data->old_working_dir = ft_strjoin("OLDPWD=", data->old_working_dir);
		if (!data->old_working_dir)
			return (0);
	}
	return (1);
}


int	setup_mini(t_data *data, t_env_info *env, char **envp)
{
	if (!ft_env_setup(env, envp))
	{
		errmsg_cmd("Fatal", NULL, ENVERRO, 1);
		return (0);
	}
	if (!init_directory(data))
	{
		errmsg_cmd("Fatal", NULL, WDWRROR, 1);
		return (0);
	}
	data->token = NULL;
	data->user_input = NULL;
	data->cmd = NULL;
	data->pid = -1;
	errno = 0;
	linked_list_print(env, envp, 1);
	//final_exit_code = 0;
	return (1);
}

void	setup_io(t_command *cmd)
{
	if (!cmd->io_fds)
	{
		cmd->io_fds = calloc(1, sizeof * cmd->io_fds);
		if (!cmd->io_fds)
			return ;
		cmd->io_fds->infile = NULL;
		cmd->io_fds->outfile = NULL;
		cmd->io_fds->heredoc_delimiter = NULL;
		cmd->io_fds->heredoc_quotes = 0;
		cmd->io_fds->fd_in = -1;
		cmd->io_fds->fd_out = -1;
		cmd->io_fds->stdin_backup = -1;
		cmd->io_fds->stdout_backup = -1;
	}
}