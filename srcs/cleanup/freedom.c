/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freedom.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzetoun <zzetoun@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 18:27:13 by zzetoun           #+#    #+#             */
/*   Updated: 2025/05/07 18:27:13 by zzetoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_io(t_io_fds *io)
{
	if (!io)
		return ;
	restore_io(io);
	if (io->infile)
		ft_free_dptr((void **)&io->infile);
	if (io->outfile)
		ft_free_dptr((void **)&io->outfile);
	if (io->append_file)
		ft_free_dptr((void **)&io->append_file);
	if (io->heredoc_delimiter)
		ft_free_dptr((void **)&io->heredoc_delimiter);
	if (io->heredoc_pipe[0] > 0)
	{
		close(io->heredoc_pipe[0]);
		io->heredoc_pipe[0] = -1;
	}
	if (io->heredoc_pipe[1] > 0)
	{
		close(io->heredoc_pipe[1]);
		io->heredoc_pipe[1] = -1;
	}
	if (io)//TODO do no free io here, because it is already freed in the cmd
		ft_free_dptr((void **)&io);
}

void	ft_close_fds(t_command *cmds, bool close_backups)
{
	if (cmds->io_fds)
	{
		if (cmds->io_fds->fd_in != -1)
			close(cmds->io_fds->fd_in);
		if (cmds->io_fds->fd_out != -1)
			close(cmds->io_fds->fd_out);
		if (close_backups)
			restore_io(cmds->io_fds);
	}
	close_pipe_fds(cmds, NULL);
}

void	ft_free_array(char **array)
{
	int	 idx;

	if (!array)
		return ;
	idx = -1;
	while (array[++idx])
	{
		free(array[idx]);
		array[idx] = NULL;
	}
	free(array);
	array = NULL;
}

void 	ft_free_dptr(void **pointer)
{
	if (pointer && *pointer)
	{
		free(*pointer);
		*pointer = NULL;
	}
}

void	ft_freedom(t_data **data, bool clear_history)
{
	if (data && (*data)->user_input)
	{
		ft_free_dptr((void **)(*data)->user_input);
		(*data)->user_input = NULL;
	}
	if (data && (*data)->cmd)
		clear_cmd(&(*data)->cmd);
	if (clear_history)
	{
		if (data && *data && (*data)->working_dir)
			ft_free_dptr((void **)&(*data)->working_dir);
		if (data && *data && (*data)->old_working_dir)
			ft_free_dptr((void **)&(*data)->old_working_dir);
		if (data && *data && (*data)->env)
			free_env((*data)->env);
		rl_clear_history();
	}
}
