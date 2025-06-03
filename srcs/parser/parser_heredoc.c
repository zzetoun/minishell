// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   parser_heredoc.c                                   :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: zzetoun <zzetoun@student.42abudhabi.ae>    +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2025/05/29 19:12:46 by zzetoun           #+#    #+#             */
// /*   Updated: 2025/05/30 16:05:51 by zzetoun          ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "../include/minishell.h"

// /* darray_to_str:
// **   Join array of strings into one space-separated string.
// */
// static char	*darray_to_str(char **tab)
// {
// 	char	*line;
// 	int		i;

// 	i = 0;
// 	line = NULL;
// 	while (tab[i])
// 	{
// 		if (i == 0)
// 			line = darray_to_str(tab[i]);
// 		else
// 			line = ft_strjoin_free(line, tab[i]);
// 		if (tab[i + 1])
// 			line = ft_strjoin_free(line, " ");
// 		i++;
// 	}
// 	ft_free_array(tab);
// 	return (line);
// }

// /* get_expanded_var_line:
// **   Expand variables in unquoted heredoc lines.
// */
// static char	*get_expanded_var_line(t_data *data, char *line)
// {
// 	char	**words;
// 	char	*res;
// 	int		idx;

// 	words = ft_split(line, ' ');
// 	if (!words)
// 		return (NULL);
// 	idx = -1;
// 	while (words[++idx])
// 	{
// 		if (ft_strchr(words[idx], '$'))
// 		{
// 			res = var_expander_heredoc(data, words[idx]);
// 			if (!res)
// 				return (NULL);
// 			ft_free_ptr(words[idx]);
// 			words[idx] = res;
// 		}
// 	}
// 	return (darray_to_str(words));
// }

// /* check_heredoc:
// **   Return false to stop on EOF or delimiter, true to write line.
// */
// static bool	check_heredoc(t_data *data, char **line, t_io_fds *io, bool *ret)
// {
// 	if (!*line)
// 	{
// 		errmsg("warning", HERDOCER, io->heredoc_delimiter, true);
// 		*ret = true;
// 		return (false);
// 	}
// 	if (ft_strncmp(*line, io->heredoc_delimiter, -1) == 0)
// 	{
// 		*ret = true;
// 		return (false);
// 	}
// 	if (!io->heredoc_quotes && ft_strchr(*line, '$'))
// 	{
// 		*line = get_expanded_var_line(data, *line);
// 		if (!*line)
// 		{
// 			*ret = false;
// 			return (false);
// 		}
// 	}
// 	return (true);
// }

// /* get_heredoc:
// **   Read from stdin and write to write_fd until delimiter or EOF.
// */
// bool	get_heredoc(t_data *data, t_io_fds *io, int write_fd)
// {
// 	char	*line;
// 	bool	ret;

// 	ret = false;
// 	line = NULL;
// 	while (1)
// 	{
// 		set_signals_interactive();
// 		line = readline("heredoc> ");
// 		set_signals_noninteractive();
// 		if (!check_heredoc(data, &line, io, &ret))
// 			break ;
// 		ft_printf(1, "%s", line);
// 		ft_free_ptr(line);
// 	}
// 	free(line);
// 	return (ret);
// }

// /* parse_heredoc:
// **   Create a pipe, get it, and set cmd->fd_in accordingly.
// */
// void parse_heredoc(t_data *data, t_command **get_last_cmd, t_token **token_lst)
// {
// 	t_command	*cmd;
// 	t_token		*temp;
// 	int			pipefd[2];
	
// 	temp = *token_lst;
// 	cmd  = get_last_cmd(*get_last_cmd);
// 	setup_io(cmd);
// 	if (pipe(pipefd) == -1)
// 		exit_full(data, errmsg("pipe", NULL, strerror(errno), 1));
// 	if (get_heredoc(data, cmd->io_fds, pipefd[1]))
// 	{
// 		close(pipefd[1]);
// 		cmd->io_fds->fd_in = pipefd[0];
// 		if (dup2(cmd->io_fds->fd_in, STDIN_FILENO) == -1)
// 			exit_full(data, errmsg("dup2", NULL, strerror(errno), 1));
// 		close(cmd->io_fds->fd_in);
// 	}
// 	else
// 		cmd->io_fds->fd_in = STDIN_FILENO;
// 	if (temp->next && temp->next->next)
// 		temp = temp->next->next;
// 	else
// 		temp = temp->next;
// 	*token_lst = temp;
// }
