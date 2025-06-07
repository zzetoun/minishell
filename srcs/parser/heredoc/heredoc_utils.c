/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzetoun <zzetoun@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 01:12:14 by igorsergeev       #+#    #+#             */
/*   Updated: 2025/06/07 18:14:47 by zzetoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* make_str_from_tab:
*	Creates a single string from an array of strings by
*	joining a string to the next.
*	Returns the string.
*/
static char	*make_str_from_tab(char **tab)
{
	char	*str;
	int		i;

	i = -1;
	while (tab[++i])
	{
		if (i == 0)
			str = ft_strdup(tab[0]);
		else
			str = ft_strjoin_free(str, tab[i]);
		if (tab[i + 1])
			str = ft_strjoin_free(str, " ");
	}
	ft_free_array(tab);
	return (str);
}

/* get_exoanded_var_line:
*	Prepares a line containing '$' for environment variable expansion.
*	Splits the line into words to avoid issues with inexistent
*	environment variables.
*	ex. $USER uses $LANGUAGE -> username uses en_US:en
*	Returns a new line with expanded variables.
*/
static char	*get_expanded_var_line(t_data *data, char *line)
{
	char	**words;
	int		i;
	char	*tmp;

	words = ft_split(line, ' ');
	if (!words)
		return (NULL);
	i = 0;
	while (words[i])
	{
		if (ft_strchr(words[i], '$'))
		{
			tmp = words[i];
			words[i] = setup_env_in_line(tmp, data);
			ft_free_dptr(tmp);
			if (!words[i])
			{
				ft_free_array(words);
				return (NULL);
			}
		}
		i++;
	}
	return (make_str_from_tab(words));
}

/* check_hdoc_input:
*	Checks whether the read line should be written to heredoc file.
*	If the line is NULL or the same as the given delimiter, returns false
*	to signify that we should stop reading with readline. Otherwise, returns
*	true.
*/
static bool	check_hdoc_input(t_data *data, char **line, t_io_fds *io, bool *ret)
{
	if (!*line)
	{
		io->heredoc_delimiter = ft_strjoin_free(io->heredoc_delimiter, "\')");
		errmsg(HERDOCER, NULL, io->heredoc_delimiter, EXIT_FAILURE);
		*ret = true;
		return (false);
	}
	if (str_compare(*line, io->heredoc_delimiter))
	{
		*ret = true;
		return (false);
	}
	if (!io->heredoc_quotes && ft_strchr(*line, '$'))
	{
		*line = get_expanded_var_line(data, *line);
		if (!(*line))
		{
			ft_free_dptr(*line);
			*ret = false;
			return (false);
		}
	}
	return (true);
}

/* fill_heredoc:
*	Copies user input into a temporary file. If user inputs an
*	environment variable
*	like $USER, expands the variable before writing to the heredoc.
*	Returns true on success, false on failure.
*/
//TODO cntrl + C = exit!
//TODO make sure to free line
bool	fill_heredoc(t_data *data, t_io_fds *io, int fd)
{
	char	*line;
	bool	ret;

	ret = false;
	line = NULL;
	while (1)
	{
		set_signals_interactive();
		line = readline("> ");
		set_signals_noninteractive();
		if (!check_hdoc_input(data, &line, io, &ret))
			break ;
		ft_printf(fd, "%s\n", line);
		ft_free_dptr(line);
	}
	ft_free_dptr(line);
	return (ret);
}
