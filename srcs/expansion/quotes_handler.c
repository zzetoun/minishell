/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzetoun <zzetoun@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 16:31:02 by zzetoun           #+#    #+#             */
/*   Updated: 2025/06/02 17:18:17 by zzetoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	count_len(char *str, int count, int idx)
{
	int	status;

	status = 0;
	while (str[idx])
	{
		if ((str[idx] == '\'' || str[idx] == '\"') && status == DEFAULT)
		{
			if (str[idx] == '\'')
				status = SQUOTE;
			if (str[idx] == '\"')
				status = DQUOTE;
			idx++;
			continue ;
		}
		else if ((str[idx] == '\'' && status == SQUOTE)
			|| (str[idx] == '\"' && status == DQUOTE))
		{
			status = DEFAULT;
			idx++;
			continue ;
		}
		count++;
		idx++;
	}
	return (count + 1);
}

bool	quotes_in_string(char *str)
{
	int	idx;

	idx = -1;
	while (str[++idx])
		if (str[idx] == '\'' || str[idx] == '\"')
			return (true);
	return (false);
}

void	handle_quotes(t_data *data)
{
	t_token	*token;

	token = data->token;
	while (token)
	{
		if (quotes_in_string(token->str) == true
			&& (!token->prev || (token->prev && token->prev->type != HEREDOC)))
			remove_quotes(&token);
		token = token->next;
	}
}
