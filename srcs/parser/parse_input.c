/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzetoun <zzetoun@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 00:20:39 by alexa             #+#    #+#             */
/*   Updated: 2025/06/02 22:15:35 by zzetoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*	INPUT -> REDIR_IN (<)
	Redirection of input causes the file whose name results from the expansion 
	of word to be opened for reading on file descriptor n, or the standard input
	(file descriptor 0) if n is not specified.

	The general format for redirecting input is: [n]<word
*/

bool	remove_old_file_ref(t_io_fds *io, bool infile)
{
	if (infile == true && io->infile)
	{
		if (io->fd_in == -1 || (io->outfile && io->fd_out == -1))
			return (false);
		if (io->heredoc_delimiter != NULL)
		{
			ft_free_ptr(io->heredoc_delimiter);
			io->heredoc_delimiter = NULL;
			unlink(io->infile);
		}
		ft_free_ptr(io->infile);
		close(io->fd_in);
	}
	else if (infile == false && io->outfile)
	{
		if (io->fd_out == -1 || (io->infile && io->fd_in == -1))
			return (false);
		ft_free_ptr(io->outfile);
		close(io->fd_out);
	}
	return (true);
}

/* open_infile:
*	Opens an infile. If an infile was already set, frees it
*	and overwrites it. If a previous infile open failed (file does
*	not exist or permission denied), does not open any further input file.
*	Ex.:
*		< Makefile <README.md cat > test
*			Uses contents of README as input (ignores Makefile)
*		< forbidden <README.md cat > test
*			Permission denied (no README cat)
*/
static void	open_infile(t_io_fds *io, char *file, char *filename)
{
	if (!remove_old_file_ref(io, true))
		return ;
	io->infile = ft_strdup(file);
	if (io->infile && io->infile[0] == '\0')
	{
		errmsg(filename, NULL, "ambiguous redirect", EXIT_FAILURE);
		return ;
	}
	io->fd_in = open(io->infile, O_RDONLY);
	if (io->fd_in == -1)
		errmsg(io->infile, NULL, strerror(errno), errno);
}

void	parse_input(t_command **last_cmd, t_token **token_list)
{
	t_token		*token;
	t_command	*cmd;

	token = *token_list;
	cmd = get_last_cmd(*last_cmd);
	setup_io(cmd);
	open_infile(cmd->io_fds, token->next->str, token->next->str_backup);
	if (token->next->next)
		token = token->next->next;
	else
		token = token->next;
	*token_list = token;
}
