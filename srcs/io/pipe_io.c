/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_io.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzetoun <zzetoun@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 16:48:20 by zzetoun           #+#    #+#             */
/*   Updated: 2025/05/23 20:54:11 by zzetoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* close_pipe_fds:
*	Closes the pipe fds of all commands. A pointer to a command to skip
*	can be specified to skip closing that command's pipe fds:
*		- The parent will specify NULL for the skip command while closing
*		all pipe fds.
*		- The child will specify its own command as skip command while
*		closing all pipe fds so as to not accidentally close its own
*		pipe fds.
*/
void	close_pipe_fds(t_command *cmds, t_command *_cmd)
{
	while (cmds)
	{
		if (cmds != _cmd && cmds->pipe_fd)
		{
			close(cmds->pipe_fd[0]);
			close(cmds->pipe_fd[1]);
		}
		cmds = cmds->next;
	}
}

/* create_pipes:
*	Creates a set of pipes for each piped command in the list
*	of commands.
*	Returns 1 if successful, 0 in case of failure.
*/
int	create_pipes(t_data *data)
{
	int			*fd;
	t_command	*tmp;

	tmp = data->cmd;
	while (tmp)
	{
		if (tmp->pipe_output || (tmp->prev && tmp->prev->pipe_output))
		{
			fd = malloc(sizeof * fd * 2);
			if (!fd || pipe(fd) != 0)
			{
				ft_freedom(data, 0);
				return (0);
			}
			tmp->pipe_fd = fd;
		}
		tmp = tmp->next;
	}
	return (1);
}

/* set_pipe_fds:
*	Sets the pipe fds for this command. If the previous command
*	was piped to this one, sets the input as the read end of
*	the previous command. If this command is piped to the
*	next, sets the output ad the write end of the pipe.
*		pipe_fd[0] = read end of pipe.
*		pipe_fd[1] = write end of pipe.
*	Returns 1 when the pipe file descriptors are set.
*/
int	set_pipe_fds(t_command *cmds, t_command *c)
{
	if (!c)
		return (0);
	if (c->prev && c->prev->pipe_output)
		dup2(c->prev->pipe_fd[0], STDIN_FILENO);
	if (c->pipe_output)
		dup2(c->pipe_fd[1], STDOUT_FILENO);
	close_pipe_fds(cmds, c);
	return (1);
}
