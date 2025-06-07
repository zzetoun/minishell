/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igorsergeevic <igorsergeevic@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 01:20:51 by igorsergeev       #+#    #+#             */
/*   Updated: 2025/06/07 03:13:28 by igorsergeev      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <readline/readline.h>
#include <readline/history.h>

bool    parse_pipe(t_command **head)
{
	t_command   *last;

	if (!head)
		return (false);
	last = get_last_cmd(*head);
	if (!last)
	{
		if (!add_back_cmd(head, add_new_cmd(false))
			|| !(last = get_last_cmd(*head))
			|| !setup_io(last))
			return (false);
	}
	last->pipe_output = true;
	if (!add_back_cmd(&last, add_new_cmd(false))
		|| !setup_io(last->next))
		return (false);
	return (true);
}

//static int	setup_redir(t_command *cmd, char **sp, int i)
//{
//	if (!cmd || !sp[i] || !sp[i + 1])
//		return (-1);
//	if (strcmp(sp[i], "<") == 0)
//	{
//		if (setup_token_type_and_give_command(cmd, sp[i + 1], INPUT))
//			return (2);
//		return (-1);
//	}
//	if (strcmp(sp[i], ">") == 0)
//	{
//		if (setup_token_type_and_give_command(cmd, sp[i + 1], TRUNC))
//			return (2);
//		return (-1);
//	}
//	if (strcmp(sp[i], ">>") == 0)
//	{
//		if (setup_token_type_and_give_command(cmd, sp[i + 1], APPEND))
//			return (2);
//		return (-1);
//	}
//	return (0);
//}

static int setup_redir(t_command *cmd, char **sp, int i)
{
	if (!cmd || !sp[i])
		return (-1);
	if (strcmp(sp[i], "<") && strcmp(sp[i], ">") && strcmp(sp[i], ">>"))
		return (0);
	if (!sp[i + 1])
		return (-1);
	if (strcmp(sp[i], "<") == 0)
		return (setup_token_type_and_give_command(cmd, sp[i + 1], INPUT) ? 2 : -1);
	if (strcmp(sp[i], ">") == 0)
		return (setup_token_type_and_give_command(cmd, sp[i + 1], TRUNC) ? 2 : -1);
	if (strcmp(sp[i], ">>") == 0)
		return (setup_token_type_and_give_command(cmd, sp[i + 1], APPEND) ? 2 : -1);

	return (0);
}

static bool	pre_check_input(char **input, t_data *data, t_command **cmd, char ***split)
{
	if (!data)
		return (false);
	(*cmd) = data->cmd;
	*input = setup_env_in_line(*input, data);
	if (!*input)
		return (false);
	*split = minishell_split(*input);
	if (!*split)
	{
		ft_free_ptr(*input);
		return (false);
	}
	return (true);
}

static bool if_not_cmd(t_data **data, t_command **cmd)
{
	if (!*cmd)
	{
		if (!add_back_cmd(&(*data)->cmd, add_new_cmd(false)))
			return (false);
		*cmd = get_last_cmd((*data)->cmd);
		if (!*cmd)
			return (false);
		if (!setup_io(*cmd))
			return (false);
	}
	return (true);
}

//int	handle_token(t_data *d, t_command **cmd, char **sp, int i)
//{
//	int	step;
//
//	if (str_compare(sp[i], "|"))
//	{
//		if (!setup_pipe_into_cmd(&d, cmd))
//			return (-1);
//		return (1);
//	}
//	*cmd = get_last_cmd(d->cmd);
//	if (!*cmd)
//	{
//		if (!if_not_cmd(&d, cmd))
//			return (-1);
//	}
//	step = setup_redir(*cmd, sp, i);
//	if (step != 0)
//		return (step);
//	if (str_compare(sp[i], "<<"))
//		return (setup_heredoc_into_cmd(d, *cmd, sp, i));
//	if (!setup_word_into_cmd(cmd, sp[i]))
//		return (-1);
//	return (1);
//}
static bool  has_any_redir(t_command *cmd)
{
	t_io_fds *io = cmd->io_fds;
	return (io && (io->infile || io->outfile || io->append_file
				   || io->heredoc_delimiter));
}

static bool  finish_segment(t_command *cmd)
{
	if (!cmd)                   /* пустого узла нет – всё ок */
		return (true);

	/* есть хотя бы один редирект, но нет слова-команды */
	if (!cmd->command && has_any_redir(cmd))
	{
		cmd->command = ft_strdup(":");          /* POSIX  no-op */
		cmd->args    = append_arg(NULL, ":");
		return (true);
	}

	/* совсем ничего – синтаксическая ошибка */
	if (!cmd->command)
	{
		ft_printf(2,
				   "Minishell: syntax error near unexpected token `|'\n");
		g_final_exit_code = 258;
		return (false);
	}
	return (true);
}

int handle_token(t_data *d, t_command **cmd, char **sp, int i)
{
	int step;

	if (str_compare(sp[i], "|"))
	{
		if (!finish_segment(*cmd) || !setup_pipe_into_cmd(&d, cmd))
			return (-1);
		return (1);
	}
	*cmd = get_last_cmd(d->cmd);
	if (!*cmd && !if_not_cmd(&d, cmd))
		return (-1);
	*cmd = get_last_cmd(d->cmd);        /* ← добавили повторное получение */

	step = setup_redir(*cmd, sp, i);
	if (step != 0)
		return (step);

	if (str_compare(sp[i], "<<"))
		return (setup_heredoc_into_cmd(d, *cmd, sp, i));

	if (!setup_word_into_cmd(cmd, sp[i]))
		return (-1);

	return (1);
}

bool	cmd_args_split(t_data *d, char *input)
{
	char		**sp;
	t_command	*cmd;
	int			i;
	int			step;

	if (!pre_check_input(&input, d, &cmd, &sp))
		return (false);
	cmd = NULL;
	d->user_input = input;
	i = 0;
	while (sp[i])
	{
		if (!cmd && !if_not_cmd(&d, &cmd))
			break ;
		step = handle_token(d, &cmd, sp, i);
		if (step < 0)
		{
			free_split(sp);
			return (false);
		}
		i += step;
	}
	if (!finish_segment(cmd))
	{
		free_split(sp);
		return (false);
	}
	free_split(sp);
	return (true);
}
