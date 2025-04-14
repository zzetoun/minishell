/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_pars.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzetoun <zzetoun@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 13:36:28 by zzetoun           #+#    #+#             */
/*   Updated: 2025/04/13 14:17:11 by zzetoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	parse_cmd_paths(t_pipex *pipex, int ac, char **av, char **envp)
{
	int		i;
	int		idx;
	char	**cmd;

	pipex->cmd_paths = ft_calloc((ac - 2 - pipex->here_doc), sizeof(char *));
	if (!pipex->cmd_paths)
		return (0);
	i = 1 + pipex->here_doc;
	while (++i < ac - 1)
	{
		idx = i - 2 - pipex->here_doc;
		cmd = ft_split(av[i], ' ');
		if (!cmd)
		{
			ft_free_array(pipex->cmd_paths, idx);
			pipex->cmd_paths = NULL;
			return (0);
		}
		pipex->cmd_paths[idx] = find_path(cmd[0], envp);
		if (pipex->cmd_paths[idx] == NULL
			&& cmd[0] && access(cmd[0], F_OK) == 0)
			pipex->cmd_paths[idx] = ft_substr(cmd[0], 0, ft_strlen(cmd[0]));
		ft_free_array(cmd, -1);
	}
	return (1);
}

int	parse_cmd_args(t_pipex *pipex, int ac, char **av)
{
	int		i;

	pipex->cmd_args = ft_calloc((ac - 2 - pipex->here_doc), sizeof(char **));
	if (!pipex->cmd_args)
		return (0);
	i = 1 + pipex->here_doc;
	while (++i < ac - 1)
	{
		pipex->cmd_args[i - 2 - pipex->here_doc] = ft_split(av[i], ' ');
		if (!pipex->cmd_args[i - 2 - pipex->here_doc])
		{
			ft_free_2d_array(pipex->cmd_args, pipex->cmd_num);
			pipex->cmd_args = NULL;
			return (0);
		}
	}
	return (1);
}

int	ft_parse(t_pipex *pipex, int ac, char **av)
{
	if (av[1] && ft_strncmp(av[1], "<<", 2) == 0
		&& ft_strlen(av[1]) == 8)
		pipex->here_doc = 1;
	if (ac < 5 + pipex->here_doc)
	{
		ft_printf(2, "pipex: error: invalid arguments Number\n");
		return (0);
	}
	pipe_infile(pipex, av);
	pipe_outfile(pipex, av, ac);
	pipex->cmd_num = ac - 3 - pipex->here_doc;
	return (1);
}

int	ft_error(char *error)
{
	ft_printf(2, "pipex: %s\n", error);
	exit(EXIT_FAILURE);
	return (1);
}

void	*ft_calloc(size_t counter, size_t size)
{
	unsigned char	*s;
	void			*ptr;
	size_t			n;

	if (size && counter > SIZE_MAX / size)
		return (NULL);
	ptr = malloc(size * counter);
	if (!ptr)
		return (NULL);
	s = (unsigned char *)ptr;
	n = size * counter;
	while (n > 0)
	{
		*s = 0;
		s++;
		n--;
	}
	return (ptr);
}
