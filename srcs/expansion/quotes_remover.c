/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_remover.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzetoun <zzetoun@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 21:38:24 by zzetoun           #+#    #+#             */
/*   Updated: 2025/06/03 21:38:26 by zzetoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	change_status_to_quote(t_token **t_node, int *i)
{
	if ((*t_node)->str[*i] == '\'')
		(*t_node)->status = SQUOTE;
	if ((*t_node)->str[*i] == '\"')
		(*t_node)->status = DQUOTE;
	(*i)++;
}

static bool	if_quotes_and_default(t_token **t_node, int i)
{
	if (((*t_node)->str[i] == '\'' || (*t_node)->str[i] == '\"')
		&& (*t_node)->status == DEFAULT)
		return (true);
	else
		return (false);
}

static bool	change_back_to_default(t_token **t_node, int *i)
{
	if (((*t_node)->str[*i] == '\'' && (*t_node)->status == SQUOTE)
		|| ((*t_node)->str[*i] == '\"' && (*t_node)->status == DQUOTE))
	{
		(*t_node)->status = DEFAULT;
		(*i)++;
		return (true);
	}
	else
		return (false);
}

void	remove_quotes(t_token **t_node)
{
	char	*new_line;
	int		idx;
	int		jdx;

	idx = 0;
	jdx = 0;
	new_line = ft_calloc(count_len((*t_node)->str, 0, 0), sizeof(char));
	if (!new_line)
		return ;
	while ((*t_node)->str[idx])
	{
		if (if_quotes_and_default(t_node, idx))
		{
			change_status_to_quote(t_node, &idx);
			continue ;
		}
		else if (change_back_to_default(t_node, &idx) == true)
			continue ;
		new_line[jdx++] = (*t_node)->str[idx++];
	}
	new_line[jdx] = '\0';
	ft_free_ptr((*t_node)->str);
	(*t_node)->str = new_line;
	(*t_node)->join = true;
}
