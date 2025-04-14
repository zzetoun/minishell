/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freedom.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzetoun <zzetoun@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 15:50:37 by zzetoun           #+#    #+#             */
/*   Updated: 2025/02/15 18:06:33 by zzetoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_free_fd(t_pipex *pipex)
{
	if (pipex->infd != -1)
	{
		close(pipex->infd);
		pipex->infd = -1;
	}
	if (pipex->outfd != -1)
	{
		close(pipex->outfd);
		pipex->outfd = -1;
	}
}

void	ft_close_fd(int fd[])
{
	if (fd[0] != -1)
	{
		close(fd[0]);
		fd[0] = -1;
	}
	if (fd[1] != -1)
	{
		close(fd[1]);
		fd[1] = -1;
	}
}

void	ft_free_array(char **array, int n)
{
	int	i;

	i = -1;
	if (n == -1)
		while (array[++i])
			(free(array[i]), array[i] = NULL);
	else
		while (++i < n)
			if (array[i])
				(free(array[i]), array[i] = NULL);
	free(array);
	array = NULL;
}

void	ft_free_2d_array(char ***array, int n)
{
	int	i;

	i = -1;
	if (n == -1)
		while (array[++i])
			ft_free_array(array[i], -1);
	else
		while (++i < n)
			if (array[i])
				ft_free_array(array[i], -1);
	free(array);
}

void	ft_freedom(t_pipex *pipex, int type)
{
	if (!pipex)
		return ;
	if (type == 1 || type == 2)
		ft_free_fd(pipex);
	if ((type == 1 || type == 3) && pipex->cmd_paths != NULL)
	{
		ft_free_array(pipex->cmd_paths, pipex->cmd_num);
		pipex->cmd_paths = NULL;
	}
	if ((type == 1 || type == 4) && pipex->cmd_args != NULL)
	{
		ft_free_2d_array(pipex->cmd_args, pipex->cmd_num);
		pipex->cmd_args = NULL;
	}
	if (type == 1 || type == 5)
	{
		free(pipex);
		pipex = NULL;
	}
}
