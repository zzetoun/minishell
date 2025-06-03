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

#include "../include/minishell.h"

void	ft_free_io(t_io_fds *io)
{
	if (!io)
		return ;
	restore_io(io);
	if (io->heredoc_delimiter)
	{
		unlink(io->infile);
		ft_free_ptr(io->heredoc_delimiter);
	}
	if (io->infile)
		ft_free_ptr(io->infile);
	if (io->outfile)
		ft_free_ptr(io->outfile);
	if (io)
		ft_free_ptr(io);
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
	char	**ptr;

	if (!array)
		return ;
	ptr = array;
	while (*ptr)
	{
		ft_free_ptr(*ptr);
		ptr++;
	}
	free(array);
	array = NULL;
}

void	ft_free_ptr(void *pointer)
{
	if (pointer != NULL)
	{
		free(pointer);
		pointer = NULL;
	}
}

void	ft_freedom(t_data *data, bool clear_history)
{
	if (data && data->user_input)
		ft_free_ptr(data->user_input);
	if (data && data->token)
		clear_token(&data->token, &ft_free_ptr);
	if (data && data->cmd)
		clear_cmd(&data->cmd, &ft_free_ptr);
	if (clear_history)
	{
		if (data && data->working_dir)
			ft_free_ptr(data->working_dir);
		if (data && data->old_working_dir)
			ft_free_ptr(data->old_working_dir);
		if (data && data->env)
			free_env(data->env);
		rl_clear_history();
	}
}
