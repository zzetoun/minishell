/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_uti.c                                      	:+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzetoun <zzetoun@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 17:41:50 by zzetoun           #+#    #+#             */
/*   Updated: 2025/01/29 18:10:53 by zzetoun          ###   ########.ae       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**get_path(char **envp)
{
	char	*paths;
	int		i;

	i = -1;
	paths = NULL;
	if (!envp)
		return (NULL);
	while (envp[++i])
		if (ft_strncmp("PATH", envp[i], ft_strlen("PATH")) == 0
			&& envp[i][ft_strlen("PATH")] == '=')
			paths = ft_strchr(envp[i], '=') + 1;
	if (!paths)
		return (NULL);
	return (ft_split(paths, ':'));
}

char	*find_path(char *cmd, char **envp)
{
	int		i;
	char	**paths;
	char	*path;

	i = -1;
	paths = get_path(envp);
	if (!paths)
		return (NULL);
	while (paths[++i])
	{
		path = ft_strjoin(paths[i], "/");
		if (!path)
			return (ft_free_array(paths, -1), NULL);
		path = ft_strjoin_gnl(path, cmd);
		if (!path)
			return (ft_free_array(paths, -1), NULL);
		if (access(path, F_OK) == 0)
			return (ft_free_array(paths, -1), path);
		free(path);
	}
	ft_free_array(paths, -1);
	return (NULL);
}

int	ft_fork_pipe(t_pipex *pipex, int fd[2], pid_t *pid, int idx)
{
	if (pipe(fd) == -1)
		return (ft_freedom(pipex, 1), exit(EXIT_FAILURE), 0);
	*pid = fork();
	if (*pid == -1)
		return (ft_close_fd(fd), ft_freedom(pipex, 1), exit(EXIT_FAILURE), 0);
	if (*pid == 0)
	{
		if (idx == 0 && pipex->in_invalid == -1)
			(ft_close_fd(fd), ft_freedom(pipex, 1), exit(EXIT_FAILURE));
		else if (idx == 0)
			dup2(pipex->infd, STDIN_FILENO);
		if (idx == pipex->cmd_num - 1 && pipex->out_invalid == -1)
			(ft_close_fd(fd), ft_freedom(pipex, 1), exit(EXIT_FAILURE));
		else if (idx == pipex->cmd_num - 1)
			dup2(pipex->outfd, STDOUT_FILENO);
		else
			dup2(fd[1], STDOUT_FILENO);
	}
	else
	{
		dup2(fd[0], STDIN_FILENO);
		ft_close_fd(fd);
	}
	return (1);
}

int	ft_child(t_pipex *pipex, char **envp, pid_t *pid, int idx)
{
	int		fd[2];

	if (!ft_fork_pipe(pipex, fd, pid, idx))
		return (0);
	if (*pid == 0)
	{
		ft_close_fd(fd);
		if (pipex->cmd_paths[idx])
		{
			ft_free_fd(pipex);
			execve(pipex->cmd_paths[idx], pipex->cmd_args[idx], envp);
			ft_printf(2, "pipex: permission denied: %s\n",
				pipex->cmd_args[idx][0]);
			ft_freedom(pipex, 1);
			exit(EPERM);
		}
		else
			ft_printf(2, "pipex: command not found: %s\n",
				pipex->cmd_args[idx][0]);
		ft_freedom(pipex, 1);
		exit(ECFND);
	}
	return (1);
}
