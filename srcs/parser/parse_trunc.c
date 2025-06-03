/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_trunc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzetoun <zzetoun@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 21:39:05 by zzetoun           #+#    #+#             */
/*   Updated: 2025/06/03 21:39:06 by zzetoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
	TRUNC -> Redirection of output.
	The file whose name results from the expansion of word has to be opened 
    in writing mode on fd n or the standard output (fd 1) if n is not specified.
    If the file does not exist it is created;
    if it does exist it is truncated to 0 size.

	The general format for redirecting output is: [n]>[|]word
*/

char	*get_relative_path(char *file_to_open)
{
	char	*path;
	char	*ret;

	if (file_to_open[0] == '/')
		return (ft_strdup(file_to_open));
	path = ft_strdup("./");
	ret = ft_strjoin(path, file_to_open);
	printf("PARSING - Get_rel_path function return : %s\n", ret);
	return (ret);
}

/* open_outfile_trunc:
*	Opens an outfile in truncated mode. If an outfile was already set, frees it
*	and overwrites it. If a previous infile or outfile open failed (file does
*	not exist or permission denied), does not open any further output file.
*
*	Ex.:
*		echo hello > forbidden_file > test
*		echo hello >> forbidden_file > test
*		< forbidden_file cat > test
*	In these 3 cases, the test file should not be opened or created.
*/
static void	open_outfile_trunc(t_io_fds *io, char *file, char *var_filename)
{
	if (!remove_old_file_ref(io, false))
		return ;
	io->outfile = ft_strdup(file);
	if (io->outfile && io->outfile[0] == '\0')
	{
		errmsg(var_filename, NULL, "ambiguous redirect", EXIT_FAILURE);
		return ;
	}
	io->fd_out = open(io->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0664);
	if (io->fd_out == -1)
		errmsg(io->outfile, NULL, strerror(errno), errno);
}

void	parse_trunc(t_command **last_cmd, t_token **token_lst)
{
	t_token		*token;
	t_command	*cmd;

	token = *token_lst;
	cmd = get_last_cmd(*last_cmd);
	setup_io(cmd);
	open_outfile_trunc(cmd->io_fds, token->next->str, token->next->str_backup);
	if (token->next->next)
		token = token->next->next;
	else
		token = token->next;
	*token_lst = token;
}
