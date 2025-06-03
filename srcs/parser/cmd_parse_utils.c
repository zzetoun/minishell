/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_parse_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzetoun <zzetoun@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 15:46:28 by zzetoun           #+#    #+#             */
/*   Updated: 2025/06/03 14:25:48 by zzetoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_command	*add_new_cmd()
{
	t_command	*new_node;

	new_node = (t_command *)ft_calloc(1, sizeof(t_command));
	if (!new_node)
	{
		errmsg("malloc", NULL, MALLERR, EXIT_FAILURE);
		return (NULL);
	}
	ft_memset(new_node, 0, sizeof(t_command));
	new_node->pipe_output = false;
	return (new_node);
}

void	add_back_cmd(t_command **list, t_command *new_node)
{
	t_command	*start;

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

t_command	*get_last_cmd(t_command *cmd)
{
	while (cmd->next)
		cmd = cmd->next;
	return (cmd);
}
