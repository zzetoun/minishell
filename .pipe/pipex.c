/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzetoun <zzetoun@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 19:33:45 by zzetoun           #+#    #+#             */
/*   Updated: 2025/01/11 19:33:45 by zzetoun          ###   ########.ae       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	setup_pipex(t_pipex *pipex)
{
	pipex->infd = -1;
	pipex->outfd = -1;
	pipex->here_doc = 0;
	pipex->in_invalid = 0;
	pipex->out_invalid = 0;
	pipex->cmd_paths = NULL;
	pipex->cmd_args = NULL;
	pipex->cmd_num = 0;
	pipex->status = -1;
	pipex->pid = -1;
}

int	main(int ac, char **av, char **envp)
{
	t_pipex	*pipex;
	int		i;
	int		status;

	pipex = malloc(sizeof(t_pipex));
	if (!pipex)
		return (ft_freedom(pipex, 1), EXIT_FAILURE);
	setup_pipex(pipex);
	if (!ft_parse(pipex, ac, av))
		return (ft_freedom(pipex, 1), EXIT_FAILURE);
	if (!parse_cmd_paths(pipex, ac, av, envp))
		return (ft_freedom(pipex, 1), ft_error(PATHE));
	if (!parse_cmd_args(pipex, ac, av))
		return (ft_freedom(pipex, 1), ft_error(ARGUE));
	i = -1;
	while (++i < pipex->cmd_num)
		if (!ft_child(pipex, envp, &pipex->pid, i))
			return (ft_freedom(pipex, 1), ft_error(EUNKN));
	i = -1;
	waitpid(pipex->pid, &pipex->status, 0);
	while (++i < pipex->cmd_num - 1)
		wait(NULL);
	status = pipex->status;
	return (ft_freedom(pipex, 1), WEXITSTATUS(status));
}
