/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzetoun <zzetoun@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 21:39:24 by zzetoun           #+#    #+#             */
/*   Updated: 2025/06/03 21:39:26 by zzetoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/* get_heredoc:
*	Opens a heredoc awaiting user input.
*	Translates any given variables into	their environment values.
*	Returns false in case of error, true if successful.
*/
bool	get_heredoc(t_data *data, t_io_fds *io)
{
	int		open_fd;
	bool	ret;

	ret = true;
	open_fd = open(io->infile, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	ret = fill_heredoc(data, io, open_fd);
	close(open_fd);
	return (ret);
}

/* get_heredoc_name:
*	Generates a unique name for the current heredoc.
*	Returns the new heredoc name.
*/
static char	*get_heredoc_name(void)
{
	static int	i;
	char		*name;
	char		*number;

	number = ft_itoa(i);
	if (!number)
		return (NULL);
	name = ft_strjoin(HEREDOC_NAME, number);
	free(number);
	i++;
	return (name);
}

/* get_delim:
*	Returns the heredoc delimiter. Quotes are removed if present
*	around the delimiter, and the quotes boolean is set to true.
*/
static char	*get_delim(char *delim, bool *quotes)
{
	int	len;

	len = ft_strlen(delim) - 1;
	if ((delim[0] == '\"' && delim[len] == '\"')
		|| (delim[0] == '\'' && delim[len] == '\''))
	{
		*quotes = true;
		return (ft_strtrim(delim, "\'\""));
	}
	return (ft_strdup(delim));
}

/* parse_heredoc:
*	Creates a temporary heredoc file which will be filled with
*	user input.
*/
void	parse_heredoc(t_data *data, t_command **l_cmd, t_token **token_ls)
{
	t_token		*token;
	t_command	*cmd;
	t_io_fds	*io;

	token = *token_ls;
	cmd = get_last_cmd(*l_cmd);
	setup_io(cmd);
	io = cmd->io_fds;
	if (!remove_old_file_ref(io, true))
		return ;
	io->infile = get_heredoc_name();
	io->heredoc_delimiter = get_delim(token->next->str, &(io->heredoc_quotes));
	if (get_heredoc(data, io))
		io->fd_in = open(io->infile, O_RDONLY);
	else
		io->fd_in = -1;
	if (token->next->next)
		token = token->next->next;
	else
		token = token->next;
	*token_ls = token;
}
