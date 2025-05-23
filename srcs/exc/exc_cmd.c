/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exc_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzetoun <zzetoun@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 14:48:39 by zzetoun           #+#    #+#             */
/*   Updated: 2025/05/23 14:48:39 by zzetoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../include/minishell.h"

int	str_compare(char const *s1, char const *s2)
{
	int	result;

	if (!s1 || !s2)
		return (errmsg(NULL, "Compare Error: strings NULL", NULL, -1));
	result = (!ft_strncmp(s1, s2, ft_strlen(s2)));
	result *= (ft_strlen(s1) == strlen(s2));
	return (result);
}

int	execute_cmd(t_data *data, t_command *cmd)
{
	int	value;

	value = CMD_NOT_FOUND;
	if (str_compare(cmd->command, "pwd"))
		value = ft_pwd(data);
	else if (str_compare(cmd->command, "cd"))
		value = ft_cd(data, cmd->args, data->env);
	else if (str_compare(cmd->command, "export"))
		value = ft_export(data->env, cmd->args);
	else if (str_compare(cmd->command, "unset"))
		value = ft_unset(data->env, cmd->args);
	else if (str_compare(cmd->command, "env"))
		value = ft_env(data->env, cmd->args, -1);
	else if (str_compare(cmd->command, "echo"))
		value = ft_echo(data->env, cmd->args);
	else if (str_compare(cmd->command, "exit"))
		value = ft_exit(data, cmd->args);
	return (value);
}
/* execute_sys_bin:
*	Executes the command's system binary file if it can be found
*	among the environment executable paths.
*	Returns CMD_NOT_FOUND if a path to the executable bin file cannot be
*	found. Returns 1 in case of failure to run existing, executable
*	file.
*/
static int	execute_sys_bin(t_data *data, t_command *cmd)
{
	if (!cmd->command || cmd->command[0] == '\0')
		return (CMD_NOT_FOUND);
	if (cmd_is_dir(cmd->command))
		return (CMD_NOT_FOUND);
	cmd->path = get_cmd_path(data, cmd->command);
	if (!cmd->path)
		return (CMD_NOT_FOUND);
	if (execve(cmd->path, cmd->args, env_tostr(data->env)) == -1)
		errmsg("execve", NULL, strerror(errno), errno);
	return (EXIT_FAILURE);
}

/* execute_local_bin:
*	Attempts to execute the given command as is, in case
*	it is a local directory file or already contains the
*	path to bin.
*	Returns CMD_NOT_FOUND if the command is not an existing executable
*	file. Returns 1 in case of failure to launch executable.
*/
static int	execute_local_bin(t_data *data, t_command *cmd)
{
	int	ret;

	ret = check_cmd_not_found(data, cmd);
	if (ret != 0)
		return (ret);
	if (execve(cmd->command, cmd->args, env_tostr(data->env)) == -1)
		return (errmsg("execve", NULL, strerror(errno), errno));
	return (EXIT_FAILURE);
}

/* execute_command:
*	Child process tries to execute the given command by setting
*	its input/output fds and searching for an executable.
*	Searching for executable in this order:
*		1. Execute builtin command
*		2. Execute system binaries for command.
*		3. Execute given command name directly (local bin)
*	If it cannot find a matching builtin or executable,
*	prints an error message.
*	Child exits with it's executed program's exit code, or 1 if
*	it could not find one.
*/
int	execute_command(t_data *data, t_command *cmd)
{
	int	ret;

	if (!cmd || !cmd->command)
		exit_full(data, errmsg("child", NULL, PARSER01, EXIT_FAILURE));
	if (!check_infile_outfile(cmd->io_fds))
		exit_full(data, EXIT_FAILURE);
	set_pipe_fds(data->cmd, cmd);
	redirect_io(cmd->io_fds);
	ft_close_fds(data->cmd, 0);
	if (ft_strchr(cmd->command, '/') == NULL)
	{
		ret = execute_cmd(data, cmd);
		if (ret != CMD_NOT_FOUND)
			exit_full(data, ret);
		ret = execute_sys_bin(data, cmd);
		if (ret != CMD_NOT_FOUND)
			exit_full(data, ret);
	}
	ret = execute_local_bin(data, cmd);
	exit_full(data, ret);
	return (ret);
}
