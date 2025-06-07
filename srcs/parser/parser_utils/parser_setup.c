/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_setup.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzetoun <zzetoun@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 01:09:54 by igorsergeev       #+#    #+#             */
/*   Updated: 2025/06/07 18:14:47 by zzetoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	setup_token_type_and_give_command(t_command *cmd, const char *str,
		enum e_token_types token_type)
{
	if (!cmd || !str)
		return (false);
	cmd->token_type = token_type;
	if (token_type == INPUT)
	{
		cmd->io_fds->infile = ft_strdup(str);
		if (!cmd->io_fds->infile)
		{
			printf("Error: Failed to allocate memory for infile\n");
			return (false);
		}
	}
	else if (token_type == TRUNC)
	{
		cmd->io_fds->outfile = ft_strdup(str);
		if (!cmd->io_fds->outfile)
		{
			printf("Error: Failed to allocate memory for outfile\n");
			return (false);
		}
	}
	else if (token_type == APPEND)
	{
		cmd->io_fds->append_file = ft_strdup(str);
		if (!cmd->io_fds->append_file)
		{
			printf("Error: Failed to allocate memory for append file\n");
			return (false);
		}
	}
	else
		printf("Error: Unknown token type %d\n", token_type);
	return (true);
}

int	setup_heredoc_into_cmd(t_data *d, t_command *cmd, char **sp, int i)
{
	t_io_fds	*io;

	if (!d || !cmd || !sp[i + 1])
		return (-1);
	io = cmd->io_fds;
	if (io->heredoc_delimiter)
	{
		ft_free_dptr(io->heredoc_delimiter);
		if (io->fd_in != -1)
			close(io->fd_in);
		io->fd_in = -1;
	}
	io->heredoc_delimiter = ft_strdup(sp[i + 1]);
	if (!io->heredoc_delimiter)
		return (-1);
	io->heredoc_quotes = has_quotes(io->heredoc_delimiter);
	parse_heredoc(d, &cmd);
	cmd->token_type = HEREDOC;
	return (2);
}

bool	setup_pipe_into_cmd(t_data **d, t_command **cmd)
{
	if (!parse_pipe(&(*d)->cmd))
		return (false);
	*cmd = get_last_cmd((*d)->cmd);
	if (!*cmd)
		return (false);
	if (!setup_io(*cmd))
		return (false);
	return (true);
}

bool    setup_word_into_cmd(t_command **cmd, char *w)
{
	if (!cmd || !*cmd || !w)
		return (false);
	if (!(*cmd)->command)
	{
		(*cmd)->token_type = WORD;
		(*cmd)->command = ft_strdup(w);
		if (!(*cmd)->command)
			return (false);
	}
	(*cmd)->args = append_arg((*cmd)->args, w);
	if (!(*cmd)->args)
	{
		if (!(*cmd)->command)
			ft_free_dptr((*cmd)->command);
		return (false);
	}
	return (true);
}
