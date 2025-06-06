
#include "../parser.h"

/* get_heredoc:
*	Opens a heredoc awaiting user input.
*	Translates any given variables into	their environment values.
*	Returns false in case of error, true if successful.
*/
bool	get_heredoc(t_data *data, t_io_fds *io)
{
	bool	ret;

	if (pipe(io->heredoc_pipe) == -1)
		return (false);
	ret = fill_heredoc(data, io, io->heredoc_pipe[1]);
	close(io->heredoc_pipe[1]);
	io->fd_in = io->heredoc_pipe[0];
	return (ret);
}

/* get_heredoc_name:
*	Generates a unique name for the current heredoc.
*	Returns the new heredoc name.
*/

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

void	parse_heredoc(t_data *data, t_command **l_cmd)
{
	t_command	*cmd;
	t_io_fds	*io;
	char		*old_delim;
	char		*new_delim;

	cmd = get_last_cmd(*l_cmd);
	io  = cmd->io_fds;
	old_delim = io->heredoc_delimiter;
	new_delim = get_delim(old_delim, &io->heredoc_quotes);
	if (!new_delim)
	{
		ft_free_ptr(old_delim);
		io->heredoc_delimiter = NULL;
		io->fd_in = -1;
		return ;
	}
	io->heredoc_delimiter = new_delim;
	ft_free_ptr(old_delim);
	if (!get_heredoc(data, io))
		io->fd_in = -1;
}
