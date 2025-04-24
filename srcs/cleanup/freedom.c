/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freedom.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzetoun <zzetoun@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 15:50:37 by zzetoun           #+#    #+#             */
/*   Updated: 2025/04/19 17:06:44 by zzetoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void static ft_close_cmd_fd(t_command *cmd)
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
	char **ptr;

	if (!array)
		return ;
	ptr = array;
	while (*ptr)
	{
		ft_free_ptr(*ptr);
		ptr++;
	}
	free(array);
	array = NULL;
}
void	ft_free_ptr(void *pointer)
{
	if (pointer != NULL)
	{
		free(pointer);
		pointer = NULL;
	}
}
void	ft_freedom(t_token *token, t_command *cmd, int type)
{
	if (!token && !cmd)
		return ;
	if (cmd && type == 1)
		ft_close_cmd_fd(cmd);
	if (type == 1)
	{
		ft_free_ptr(cmd);
		ft_free_ptr(token);
	}
}
void ft_free_env(t_env_info *env)
{
	t_envp	*list;

	list = env->head;
	while (list)
	{
		list = list->next;
		env->head->idx = 0;
        free(env->head->str);
		free(env->head);
		env->head = list;
	}
    env->size = 0;
}
