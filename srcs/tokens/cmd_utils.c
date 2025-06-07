/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzetoun <zzetoun@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 15:46:28 by zzetoun           #+#    #+#             */
/*   Updated: 2025/06/07 19:06:06 by zzetoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_command	*add_new_cmd(bool value)
{
    t_command	*new_node;

    new_node = (t_command *)ft_calloc(1, sizeof(t_command));
    if (!new_node)
    {
        errmsg("malloc", NULL, MALLERR, EXIT_FAILURE);
        return (NULL);
    }
    ft_memset(new_node, 0, sizeof(t_command));
    new_node->pipe_output = value;
    return (new_node);
}

bool	add_back_cmd(t_command **list, t_command *new_node)
{
    t_command	*start;

    start = *list;
    if (start == NULL)
    {
        *list = new_node;
        return (true);
    }
    if (list && *list && new_node)
    {
        while (start->next)
            start = start->next;
        start->next = new_node;
        new_node->prev = start;
        return (true);
    }
    else
    {
        errmsg("add_back_cmd", NULL, "ERROR: list or new_node is NULL", EXIT_FAILURE);
        return (false);
    }
}

t_command	*last_cmd(t_command *cmd)
{
    while (cmd->next != NULL)
        cmd = cmd->next;
    return (cmd);
}
