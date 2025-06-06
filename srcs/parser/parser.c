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

void	parse_pipe(t_command **head)
{
	t_command *last;

	last = get_last_cmd(*head);
	if (!last)
	{
		add_back_cmd(head, add_new_cmd(false));
		last = get_last_cmd(*head);
		setup_io(last);
	}
	last->pipe_output = true;
	add_back_cmd(&last, add_new_cmd(false));
	setup_io(last->next);
}

static bool setup_current_cmd_redir(t_data *data, t_command **cmd, char **split, int *i)
{
	bool	res;

	if (!data || !cmd || !*cmd)
		return (false);
	res = false;
	if (strcmp(split[(*i)], "<") == 0 && split[(*i) + 1])
		res = setup_token_type_and_give_command(*cmd, split[++(*i)], INPUT);
	else if (strcmp(split[(*i)], ">") == 0 && split[(*i) + 1])
		res = setup_token_type_and_give_command(*cmd, split[++(*i)], TRUNC);
	else if (strcmp(split[(*i)], ">>") == 0 && split[(*i) + 1])
		res = setup_token_type_and_give_command(*cmd, split[++(*i)], APPEND);
	return (res);
}

static bool setup_current_cmd_command(t_data **data, t_command **cmd, char *word)
{
	if (!data || !*data || !cmd || !*cmd || !word)
		return (false);
	if (cmd && (*cmd) && !(*cmd)->command)
		setup_word_into_cmd(data, cmd, word);
	else if (cmd && (*cmd) && (*cmd)->command)
	{
		(*cmd)->args = append_arg((*cmd)->args, word);
		if (!(*cmd)->args)
			return (false);
	}
	return (true);
}

static bool	pre_check_input(char **input, t_data *data, t_command **cmd, char ***split)
{
	if (!data)
		return (false);
	add_history(*input);
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

static void if_not_cmd(t_data **data, t_command **cmd)
{
	if (!*cmd)
	{
		if (!add_back_cmd(&(*data)->cmd, add_new_cmd(false)))
			return (false);
		*cmd = get_last_cmd((*data)->cmd);
		setup_io(*cmd);
	}
	return ;
}

static bool handle_token(t_data *data, t_command **cmd, char **split, int *i)
{
    if (str_compare(split[*i], "|"))
        return setup_pipe_into_cmd(&data, cmd);

    *cmd = get_last_cmd(data->cmd);
    if (setup_current_cmd_redir(data, cmd, split, i))
        return true;

    if (str_compare(split[*i], "<<") && split[*i + 1])
        return setup_heredoc_into_cmd(&data, cmd, split, i);

    setup_current_cmd_command(&data, cmd, split[*i]);
    return true;
}

static void cleanup(char **split, char *input)
{
    free_split(split);
    // ft_free_ptr(input);
}

// bool		cmd_args_split(t_data *data, char *input)
// {
//     char	**split;
//     int		i;
//     t_command *cmd;

//     if (!pre_check_input(&input, data, &cmd, &split))
// 		return (false);
//     i = -1;
//     while (split[++i])
//     {
//         if (!cmd)
//         	if_not_cmd(&data, &cmd);
//         if (str_compare(split[i], "|"))
//         {
//             if (!setup_pipe_into_cmd(&data, &cmd))
// 				return (false);
//             continue;
//         }
//         cmd = get_last_cmd(data->cmd);
//         if (setup_current_cmd_redir(data, &cmd, split, &i))
// 				continue;
//         else if (str_compare(split[i], "<<") && split[i + 1])
// 		{
// 			if (!setup_heredoc_into_cmd(&data, &cmd, split, &i))
// 			{
// 				free_split(split);
// 				ft_free_ptr(input);
// 				return (false);
// 			}
// 		}
//         else
// 			setup_current_cmd_command(&data, &cmd, split[i]);
//     }
//     free_split(split);
// 	ft_free_ptr(input);
//     return (true);
// }

bool cmd_args_split(t_data *data, char *input)
{
    char        **split;
    int          i;
    t_command   *cmd;

    if (!pre_check_input(&input, data, &cmd, &split))
        return false;
    cmd = NULL;
    i = 0;
    while (split[i])
    {
        if (!cmd)
            if_not_cmd(&data, &cmd);
        if (!handle_token(data, &cmd, split, &i))
        {
            cleanup(split, input);
            return false;
        }
        i++;
    }
    cleanup(split, input);
    return true;
}
