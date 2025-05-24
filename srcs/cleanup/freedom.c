/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freedom.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzetoun <zzetoun@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 18:27:13 by zzetoun           #+#    #+#             */
/*   Updated: 2025/05/07 18:27:13 by zzetoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// static void		 ft_close_cmd_fd(t_command *cmd)
// {
// 	if (cmd->io_fds->fd_in != -1)
// 	{
// 		close(cmd->io_fds->fd_in);
// 		cmd->io_fds->fd_in = -1;
// 	}
// 	if (cmd->io_fds->fd_out != -1)
// 	{
// 		close(cmd->io_fds->fd_out);
// 		cmd->io_fds->fd_out = -1;
// 	}
// 	if (cmd->pipe_fd[0] != -1)
// 	{
// 		close(cmd->pipe_fd[0]);
// 		cmd->pipe_fd[0] = -1;
// 	}
// 	if (cmd->pipe_fd[1] != -1)
// 	{
// 		close(cmd->pipe_fd[1]);
// 		cmd->pipe_fd[1] = -1;
// 	}
// }

void	ft_close_fds(t_command *cmds, int close_backups)
{
	if (cmds->io_fds)
	{
		if (cmds->io_fds->fd_in != -1)
			close(cmds->io_fds->fd_in);
		if (cmds->io_fds->fd_out != -1)
			close(cmds->io_fds->fd_out);
		if (close_backups)
			restore_io(cmds->io_fds);
	}
	close_pipe_fds(cmds, NULL);
}

void	ft_free_array(char **array)
{
	char	**ptr;

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

void	free_env(t_env_info *env)
{
	t_envp	*list;

	list = env->head;
	while (list)
	{
		list = list->next;
		env->head->idx = 0;
		free(env->head->str);
		free(env->head->key);
		free(env->head->value);
		free(env->head);
		env->head = list;
	}
	env->size = 0;
}

void	ft_freedom(t_data *data, bool clear_history)
{
	if (data && data->user_input)
	{
		ft_free_ptr(data->user_input);
		data->user_input = NULL;
	}
	// if (data && data->token)
	// 	clear_token();
	// if (data && data->cmd)
	// 	clear_cmd();
	if (clear_history)
	{
		if (data && data->working_dir)
			ft_free_ptr(data->working_dir);
		if (data && data->old_working_dir)
			ft_free_ptr(data->old_working_dir);
		if (data && data->env)
			free_env(data->env);
		rl_clear_history();
	}
}
