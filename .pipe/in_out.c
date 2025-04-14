/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in_out.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzetoun <zzetoun@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 13:41:45 by zzetoun           #+#    #+#             */
/*   Updated: 2025/02/15 18:07:13 by zzetoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	read_here_doc(t_pipex *pipex, char **av, int *fd)
{
	char	*doc;

	ft_freedom(pipex, 1);
	close(fd[0]);
	ft_printf(1, "pipex here_doc >: ");
	while (1)
	{
		doc = get_next_line(STDIN_FILENO);
		if (!doc || (ft_strlen(doc) > 0 && doc[ft_strlen(doc) - 1] == '\n'
				&& ft_strncmp(doc, av[2], ft_strlen(av[2])) == 0
				&& ft_strlen(av[2]) == ft_strlen(doc) - 1))
		{
			if (doc)
			{
				free(doc);
				get_next_line(-1);
			}
			close(fd[1]);
			exit(EXIT_SUCCESS);
		}
		ft_printf(fd[1], "%s", doc);
		free(doc);
		ft_printf(1, "pipex here_doc >: ");
	}
}

void	pipe_here_doc(t_pipex *pipex, char **av)
{
	int		fd[2];
	pid_t	pid;

	if (pipe(fd) == -1)
	{
		perror("here_doc: pipe");
		exit(EXIT_FAILURE);
	}
	pid = fork();
	if (pid == -1)
	{
		ft_close_fd(fd);
		perror("here_doc: fork");
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
		read_here_doc(pipex, av, fd);
	else
	{
		wait(NULL);
		dup2(fd[0], STDIN_FILENO);
		ft_close_fd(fd);
	}
}

void	pipe_infile(t_pipex *pipex, char **av)
{
	if (pipex->here_doc)
		pipe_here_doc(pipex, av);
	else
	{
		if (access(av[1], F_OK | R_OK) == -1)
		{
			perror("pipex in file");
			pipex->in_invalid = -1;
		}
		else
			pipex->infd = open(av[1], O_RDONLY);
	}
}

void	pipe_outfile(t_pipex *pipex, char **av, int ac)
{
	int	flags;

	flags = O_RDWR | O_CREAT | O_TRUNC;
	pipex->outfd = open(av[ac - 1], flags, 0644);
	if (pipex->outfd == -1)
	{
		perror("pipex out file");
		pipex->out_invalid = -1;
	}
}

char	*ft_strjoin_gnl(char *s1, char *s2)
{
	char	*str;
	int		i;
	int		j;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	str = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!str)
		return (NULL);
	i = -1;
	while (s1[++i])
		str[i] = s1[i];
	j = 0;
	while (s2[j])
		str[i++] = s2[j++];
	str[i] = '\0';
	free(s1);
	return (str);
}
