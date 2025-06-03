/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_if_var.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzetoun <zzetoun@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 23:40:24 by alexa             #+#    #+#             */
/*   Updated: 2025/06/02 22:23:46 by zzetoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	variable_check(t_token **t_node)
{
	int	idx;

	idx = -1;
	while ((*t_node)->str[++idx])
	{
		if ((*t_node)->str[idx] == '$')
		{	
			if ((*t_node)->prev && (*t_node)->prev->type == HEREDOC)
				break ;
			(*t_node)->type = VAR;
			return ;
		}
	}
}

bool	check_if_var(t_token **token_list)
{
	t_token	*token;

	token = *token_list;
	if (token->type == PIPE)
	{
		errmsg(TOKENER, NULL, token->str, EXIT_FAILURE);
		return (false);
	}
	while (token)
	{
		variable_check(&token);
		if (!check_consecutives(&token))
			return (false);
		token = token->next;
	}
	return (true);
}
