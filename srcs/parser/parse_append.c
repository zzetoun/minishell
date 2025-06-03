/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_append.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzetoun <zzetoun@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 21:39:37 by zzetoun           #+#    #+#             */
/*   Updated: 2025/06/03 21:39:39 by zzetoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
	***APPEND***
	Redirection of output in append mode causes the file whose name results 
	from the expansion of word to be opened for appending on file descriptor n, 
	or the standard output (fd 1) if n is not specified. 
	If the file does not exist it is created.

	The general format for appending output is: [n]>>word.

*/

/* open_outfile_append:
*	Opens an outfile in append mode. If an outfile was already set, frees it
*	and overwrites it. If a previous infile or outfile open failed (file does
*	not exist or permission denied), does not open any further output file.
*
*	Ex.:
*		echo hello > forbidden_file >> test
*		echo hello >> forbidden_file >> test
*		< forbidden_file cat >> test
*	In these 3 cases, the test file should not be opened or created.
*/
static void	open_outfile_append(t_io_fds *io, char *file, char *var_filename)
{
	if (!remove_old_file_ref(io, false))
		return ;
	io->outfile = ft_strdup(file);
	if (io->outfile && io->outfile[0] == '\0' && var_filename)
	{
		errmsg(var_filename, NULL, "ambiguous redirect", EXIT_FAILURE);
		return ;
	}
	io->fd_out = open(io->outfile, O_WRONLY | O_CREAT | O_APPEND, 0664);
	if (io->fd_out == -1)
		errmsg(io->outfile, NULL, strerror(errno), errno);
}

void	parse_append(t_command **last_cmd, t_token **token_list)
{
	t_token		*token;
	t_command	*cmd;

	token = *token_list;
	cmd = get_last_cmd(*last_cmd);
	setup_io(cmd);
	open_outfile_append(cmd->io_fds, token->next->str, token->next->str_backup);
	if (token->next->next)
		token = token->next->next;
	else
		token = token->next;
	*token_list = token;
}
