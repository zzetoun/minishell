/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_word.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzetoun <zzetoun@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 21:38:59 by zzetoun           #+#    #+#             */
/*   Updated: 2025/06/03 21:39:00 by zzetoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static bool	contains_space(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == ' ')
			return (true);
		i++;
	}
	return (false);
}

static void	split_var_cmd_token(t_command *last_cmd, char *cmd_str)
{
	t_token		*new_tokens;
	t_token		*token;
	char		**strs;
	int			i;

	new_tokens = NULL;
	strs = ft_split(cmd_str, ' ');
	if (!strs)
		return ;
	last_cmd->command = ft_strdup(strs[0]);
	if (strs[1])
		new_tokens = add_new_token(ft_strdup(strs[1]), NULL, WORD, DEFAULT);
	token = new_tokens;
	i = 1;
	while (strs[++i])
		add_back_token(&new_tokens,
			add_new_token(ft_strdup(strs[i]), NULL, WORD, DEFAULT));
	add_back_token(&new_tokens,
		add_new_token(NULL, NULL, END, DEFAULT));
	fill_args(&new_tokens, last_cmd);
	clear_token(&token, &ft_free_ptr);
	ft_free_array(strs);
}

void	parse_word(t_command **cmd, t_token **token_lst)
{
	t_token		*token;
	t_command	*last_cmd;

	token = *token_lst;
	while (token->type == WORD || token->type == VAR)
	{
		last_cmd = get_last_cmd(*cmd);
		if (token->prev == NULL || (token->prev && token->prev->type == PIPE)
			|| last_cmd->command == NULL)
		{
			if (token->type == VAR && contains_space(token->str))
				split_var_cmd_token(last_cmd, token->str);
			else
				last_cmd->command = ft_strdup(token->str);
			token = token->next;
		}
		else
			fill_args(&token, last_cmd);
	}
	*token_lst = token;
}
