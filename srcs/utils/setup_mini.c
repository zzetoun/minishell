/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_mini.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzetoun <zzetoun@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 16:01:53 by zzetoun           #+#    #+#             */
/*   Updated: 2025/04/17 16:22:19 by zzetoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// static int	init_env(t_data *data, char **env)
// {
// 	int		i;

// 	data->env = ft_calloc(env_var_count(env) + 1, sizeof * data->env);
// 	if (!data->env)
// 		return (0);
// 	i = 0;
// 	while (env[i])
// 	{
// 		data->env[i] = ft_strdup(env[i]);
// 		if (!data->env[i])
// 			return (0);
// 		i++;
// 	}
// 	return (1);
// }

static int	init_directory(t_data *data)
{
	char	buff[PATH_MAX];
	char	*wd;

	wd = getcwd(buff, PATH_MAX);
	data->working_dir = ft_strdup(wd);
	if (!data->working_dir)
		return (0);
	// if (get_env_var_index(data->env, "OLDPWD") != -1)
	// {
	// 	data->old_working_dir = ft_strdup(get_env_var_value(data->env,
	// 				"OLDPWD"));
	// 	if (!data->old_working_dir)
	// 		return (0);
	// }
	// else
	// {
	// 	data->old_working_dir = ft_strdup(wd);
	// 	if (!data->old_working_dir)
	// 		return (0);
	// }
    data->old_working_dir = ft_strdup(wd);
	if (!data->old_working_dir)
		return (0);
	return (1);
}


int	setup_mini(t_data *data, char **env)
{
    (void) env;
	// if (!init_env(data, env))
	// {
	// 	errmsg_cmd("Fatal", NULL, ENVERRO, 1);
	// 	return (0);
	// }
	if (!init_directory(data))
	{
		errmsg_cmd("Fatal", NULL, WDWRROR, 1);
		return (0);
	}
	data->token = NULL;
	data->user_input = NULL;
	data->cmd = NULL;
	data->pid = -1;
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