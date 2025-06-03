/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_lst_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzetoun <zzetoun@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 15:40:15 by zzetoun           #+#    #+#             */
/*   Updated: 2025/06/02 15:47:53 by zzetoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_token	*add_new_token(char *str, char *str_backup, int type, int status)
{
	t_token	*new_node;

	new_node = ft_calloc(1, sizeof(t_token));
	if (!(new_node))
	{
		errmsg("malloc", NULL, MALLERR, 0);
		return (NULL);
	}
	new_node->str = str;
	new_node->str_backup = str_backup;
	new_node->var_exists = false;
	new_node->type = type;
	new_node->status = status;
	new_node->join = false;
	new_node->prev = NULL;
	new_node->next = NULL;
	return (new_node);
}

void	add_back_token(t_token **list, t_token *new_node)
{
	t_token	*start;

	start = *list;
	if (!start)
	{
		*list = new_node;
		return ;
	}
	if (list && *list && new_node)
	{
		while (start->next)
			start = start->next;
		start->next = new_node;
		new_node->prev = start;
	}
}

void	del_one_token(t_token *list, void (*del)(void *))
{
	if (del && list && list->str)
	{	
		(*del)(list->str);
		list->str = NULL;
	}
	if (del && list && list->str_backup)
	{	
		(*del)(list->str_backup);
		list->str_backup = NULL;
	}
	if (list->prev)
		list->prev->next = list->next;
	if (list->next)
		list->next->prev = list->prev;
	ft_free_ptr(list);
}

void	clear_token(t_token **list, void (*del)(void *))
{
	t_token	*tmp;

	tmp = NULL;
	while (*list)
	{
		tmp = (*list)->next;
		del_one_token(*list, del);
		*list = tmp;
	}
}
