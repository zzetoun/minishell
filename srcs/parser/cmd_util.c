/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_util.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzetoun <zzetoun@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 01:18:16 by igorsergeev       #+#    #+#             */
/*   Updated: 2025/06/07 18:32:09 by zzetoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clear_cmd(t_command **lst)
{
	t_command	*next;

	next = NULL;
	while (*lst != NULL)
	{
		
		next = (*lst)->next;
		if ((*lst)->command)
			ft_free_dptr((void **)&(*lst)->command);
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
			ft_free_dptr((void **)(*lst)->pipe_fd);
		}
		ft_free_dptr((void **)lst);
		*lst = next;
	}
}
