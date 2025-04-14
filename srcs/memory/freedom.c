/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freedom.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzetoun <zzetoun@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 15:50:37 by zzetoun           #+#    #+#             */
/*   Updated: 2025/04/14 16:24:51 by zzetoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_free_fd(t_command *cmd)
{
	if (cmd->io_fds->fd_in != -1)
	{
		close(cmd->io_fds->fd_in);
		cmd->io_fds->fd_in = -1;
	}
	if (cmd->io_fds->fd_out != -1)
	{
		close(cmd->io_fds->fd_out);
		cmd->io_fds->fd_out = -1;
	}
	if (cmd->pipe_fd[0] != -1)
	{
		close(cmd->pipe_fd[0]);
		cmd->pipe_fd[0] = -1;
	}
	if (cmd->pipe_fd[1] != -1)
	{
		close(cmd->pipe_fd[1]);
		cmd->pipe_fd[1] = -1;
	}
}

void	ft_free_array(char **array)
{
	int	i;

	i = -1;
	if (!array)
		exit(EXIT_FAILURE);
	while (array[++i])
	{
		free(array[i]);
		array[i] = NULL;
	}
	free(array);
	array = NULL;
}
void	free_ptr(void *ptr)
{
	if (ptr != NULL)
	{
		free(ptr);
		ptr = NULL;
	}
}
// void	ft_freedom_token(t_token *token, int type)
// {
// 	if (!token)
// 		return ;
// 	if (type == 1 || type == 2)
// 		ft_free_fd(token);
// 	if ((type == 1 || type == 3) && token->cmd_paths != NULL)
// 	{
// 		ft_free_array(token->cmd_paths, token->cmd_num);
// 		token->cmd_paths = NULL;
// 	}
// 	if ((type == 1 || type == 4) && token->cmd_args != NULL)
// 	{
// 		ft_free_2d_array(token->cmd_args, token->cmd_num);
// 		token->cmd_args = NULL;
// 	}
// 	if (type == 1 || type == 5)
// 	{
// 		free(token);
// 		token = NULL;
// 	}
// }
