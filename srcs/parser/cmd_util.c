/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_util.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igorsergeevic <igorsergeevic@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 01:18:16 by igorsergeev       #+#    #+#             */
/*   Updated: 2025/06/07 02:53:51 by igorsergeev      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include//minishell.h"

void	clear_cmd(t_command **lst, void (*del)(void *))
{
	t_command	*next;

	next = NULL;
	while (*lst != NULL)
	{
		
		next = (*lst)->next;
		if ((*lst)->command)
			(*del)((*lst)->command);
		if ((*lst)->args)
			ft_free_array((*lst)->args);
		if ((*lst)->io_fds)
			ft_free_io((*lst)->io_fds);
		if ((*lst)->pipe_fd)
		{
			if ((*lst)->pipe_fd[0] != -1)
				close((*lst)->pipe_fd[0]);
			if ((*lst)->pipe_fd[1] != -1)
				close((*lst)->pipe_fd[1]);
			ft_free_ptr((*lst)->pipe_fd);
		}
		(*del)((*lst));
		*lst = next;
	}
}
