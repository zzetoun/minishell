/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_grammar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzetoun <zzetoun@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 21:40:07 by zzetoun           #+#    #+#             */
/*   Updated: 2025/06/03 21:40:09 by zzetoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static bool	consecutive_ops(t_token *t_node)
{
	if (t_node->prev)
	{
		if (t_node->type == PIPE && t_node->prev->type == PIPE)
			return (true);
		if (t_node->type > PIPE && t_node->prev->type > PIPE)
			return (true);
		if (t_node->type == END && t_node->prev->type >= PIPE)
			return (true);
	}
	return (false);
}

bool	check_consecutives(t_token **token_lst)
{
	t_token	*temp;

	temp = *token_lst;
	while (temp)
	{
		if (consecutive_ops(temp) == true)
		{
			if (temp->type == END && temp->prev && temp->prev->type > PIPE)
				errmsg(TOKENER, NULL, "newline", EXIT_FAILURE);
			else if (temp->type == END && temp->prev)
				errmsg(TOKENER, NULL, temp->prev->str, EXIT_FAILURE);
			else
				errmsg(TOKENER, NULL, temp->str, EXIT_FAILURE);
			return (false);
		}
		temp = temp->next;
	}
	return (true);
}
