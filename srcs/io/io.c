/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzetoun <zzetoun@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 16:42:26 by zzetoun           #+#    #+#             */
/*   Updated: 2025/04/17 21:06:17 by zzetoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	restore_io(t_io_fds *io)
{
	int	value;

	value = EXIT_SUCCESS;
	if (!io)
		return (value);
	if (io->stdin_backup != -1)
	{
		if (dup2(io->stdin_backup, STDIN_FILENO) == -1)
			value = EXIT_FAILURE;
		close(io->stdin_backup);
		io->stdin_backup = -1;
	}
	if (io->stdout_backup != -1)
	{
		if (dup2(io->stdout_backup, STDOUT_FILENO) == -1)
			value = EXIT_FAILURE;
		close(io->stdout_backup);
		io->stdout_backup = -1;
	}
	return (value);
}

int	redirect_io(t_io_fds *io)
{
	int	r;

	r = EXIT_SUCCESS;
	if (!io)
		return (r);
	io->stdin_backup = dup(STDIN_FILENO);
	if (io->stdin_backup == -1)
		r = errmsg_cmd("dup", "stdin backup", strerror(errno), EXIT_FAILURE);
	io->stdout_backup = dup(STDOUT_FILENO);
	if (io->stdout_backup == -1)
		r = errmsg_cmd("dup", "stdout backup", strerror(errno), EXIT_FAILURE);
	if (io->fd_in != -1)
		if (dup2(io->fd_in, STDIN_FILENO) == -1)
			r = errmsg_cmd("dup2", io->infile, strerror(errno), EXIT_FAILURE);
	if (io->fd_out != -1)
		if (dup2(io->fd_out, STDOUT_FILENO) == -1)
			r = errmsg_cmd("dup2", io->outfile, strerror(errno), EXIT_FAILURE);
	return (r);
}


int	check_infile_outfile(t_io_fds *io)
{
	if (!io || (!io->infile && !io->outfile))
		return (EXIT_SUCCESS);
	if ((io->infile && io->fd_in == -1)
		|| (io->outfile && io->fd_out == -1))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}