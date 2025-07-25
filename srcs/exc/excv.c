/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   excv.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzetoun <zzetoun@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 14:50:44 by zzetoun           #+#    #+#             */
/*   Updated: 2025/06/07 20:17:36 by zzetoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* get_children:
*	Waits for children to terminate after cleaning up fds and the command
*	list.
*	Returns a child's exit status as bash does:
*		"The return status (see Exit Status) of a simple command is its
*		exit status as provided by the POSIX 1003.1 waitpid function, or
*		128+n if the command was terminated by signal n."
*	If there are multiple commands in a pipeline:
*		"The exit status of a pipeline is the exit status of the last command
*		in the pipeline"
*/
static int	get_children(t_data *data)
{
	pid_t	wpid;
	int		status;
	int		save_status;

	ft_close_fds(data->cmd, 0);
	save_status = 0;
	wpid = 0;
	while (wpid != -1 || errno != ECHILD)
	{
		wpid = waitpid(-1, &status, 0);
		if (wpid == data->pid)
			save_status = status;
		continue ;
	}
	if (WIFSIGNALED(save_status))
		status = 128 + WTERMSIG(save_status);
	else if (WIFEXITED(save_status))
		status = WEXITSTATUS(save_status);
	else
		status = save_status;
	return (status);
}

/* create_children:
*	Creates a child process for each command to execute, except in the
*	case of a builtin command that is not piped, which executes in the
*	main process (no children created in this case).
*	Returns true when a process was created for each command or when a
*	builtin was executed alone.
*	Returns false if there was a fork error.
*/

static int	create_children(t_data *data)
{
	t_command	*cmd;

	cmd = data->cmd;
	while (data->pid != 0 && cmd)
	{
		data->pid = fork();
		if (data->pid == -1)
			return (errmsg("fork", NULL, strerror(errno), errno));
		else if (data->pid == 0)
		{
			if (cmd->io_fds && cmd->io_fds->infile)
				setup_input(cmd->io_fds);
			if (cmd->io_fds && cmd->io_fds->outfile)
				setup_truncate(cmd->io_fds);
			if (cmd->io_fds && cmd->io_fds->append_file)
				setup_append(cmd->io_fds);
			execute_command(data, cmd);
			if (data->cmd->io_fds->heredoc_delimiter)
				ft_free_dptr((void **)&data->cmd->io_fds->heredoc_delimiter);
			close_exists_red_fds(cmd->io_fds);
			restore_io(cmd->io_fds);
		}
		cmd = cmd->next;
	}
	return (get_children(data));
}

/* prep_for_exec:
*	Prepares the command list for execution, creates pipes
*	and checks the input and output files.
*	Returns false in case of error, true if all is ready to
*	execute.
*/
static int	prep_for_exec(t_data *data)
{
	if (!data || !data->cmd)
		return (EXIT_SUCCESS);
	if (!data->cmd->command)
	{
		if (data->cmd->io_fds && !check_io(data->cmd->io_fds))
			return (EXIT_FAILURE);
		return (EXIT_SUCCESS);
	}
	if (!create_pipes(data))
		return (EXIT_FAILURE);
	return (CMD_NOT_FOUND);
}

/* execute:
*	Executes the given commands by creating children processes
*	and waiting for them to terminate.
*	Returns the exit code of the last child to terminate. Or
*	exit code 1 in case of failure in the child creation process.
*/
int	execute(t_data *data)
{
	int	ret;

	ret = prep_for_exec(data);
	if (ret != CMD_NOT_FOUND)
		return (ret);
	if (!data->cmd->pipe_output && !data->cmd->prev
		&& check_io(data->cmd->io_fds))
	{
		redirect_io(data->cmd->io_fds);
		ret = execute_bcmd(data, data->cmd);
		restore_io(data->cmd->io_fds);
	}
	if (ret != CMD_NOT_FOUND)
		return (ret);
	return (create_children(data));
}
