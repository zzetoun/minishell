/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_io.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzetoun <zzetoun@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 16:47:56 by zzetoun           #+#    #+#             */
/*   Updated: 2025/05/23 19:48:00 by zzetoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../include/minishell.h"

/* restore_io:
*	Restores the original standard input and standard output
*	to their original fds of 0 and 1. Used to clear the input/output
*	fds after execution, in preparation for the next set of user commands.
*	Returns 1 if the duplication was successful, 0 if not.
*/
int	restore_io(t_io_fds *io)
{
	int	status;

	status = EXIT_SUCCESS;
	if (!io)
		return (status);
	if (io->stdin_backup != -1)
	{
		if (dup2(io->stdin_backup, STDIN_FILENO) == -1)
			status = EXIT_FAILURE;
		close(io->stdin_backup);
		io->stdin_backup = -1;
	}
	if (io->stdout_backup != -1)
	{
		if (dup2(io->stdout_backup, STDOUT_FILENO) == -1)
			status = EXIT_FAILURE;
		close(io->stdout_backup);
		io->stdout_backup = -1;
	}
	return (status);
}
/* redirect_io:
*	Duplicates the input and output fds to the standard input and output.
*	Backs up the standard input and output before replacing them in order
*	to restore them after execution.
*	Returns 1 for success, 0 in case of error.
*/
int	redirect_io(t_io_fds *io)
{
	int	status;

	status = EXIT_SUCCESS;
	if (!io)
		return (status);
	io->stdin_backup = dup(STDIN_FILENO);
	if (io->stdin_backup == -1)
		status = errmsg("dup", "stdin backup", strerror(errno), 1);
	io->stdout_backup = dup(STDOUT_FILENO);
	if (io->stdout_backup == -1)
		status = errmsg("dup", "stdout backup", strerror(errno), 1);
	if (io->fd_in != -1)
		if (dup2(io->fd_in, STDIN_FILENO) == -1)
			status = errmsg("dup2", io->infile, strerror(errno), 1);
	if (io->fd_out != -1)
		if (dup2(io->fd_out, STDOUT_FILENO) == -1)
			status = errmsg("dup2", io->outfile, strerror(errno), 1);
	return (status);
}
/* check_infile_outfile:
*	Checks if the infile and outfile are set correctly.
*	Returns 1 on success, 0 on failure.
*/
int	check_infile_outfile(t_io_fds *io)
{
	if (!io || (!io->infile && !io->outfile))
		return (EXIT_SUCCESS);
	if ((io->infile && io->fd_in == -1)
		|| (io->outfile && io->fd_out == -1))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
