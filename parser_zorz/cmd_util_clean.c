/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_util_clean.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzetoun <zzetoun@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 15:48:26 by zzetoun           #+#    #+#             */
/*   Updated: 2025/05/25 18:36:54 by zzetoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	list_del_cmd(t_command *list, void (*del)(void *))
{
	if (list->command)
		(*del)(list->command);
	if (list->args)
		ft_free_array(list->args);
	if (list->pipe_fd)
		(*del)(list->pipe_fd);
	if (list->io_fds)
		ft_free_io(list->io_fds);
	(*del)(list);
}

void	list_clear_cmd(t_command **list, void (*del)(void *))
{
	t_command	*temp;

	temp = NULL;
	while (*list != NULL)
	{
		temp = (*list)->next;
		list_del_cmd(*list, del);
		*list = temp;
	}
}
