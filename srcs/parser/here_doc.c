// #include "../../include/minishell.h"

// void	read_here_doc(t_data *data, char **av, int *fd)
// {
// 	char	*doc;

// 	ft_freedom(data, 1);
// 	close(fd[0]);
// 	while (1)
// 	{
// 		doc = readline("");
// 		if (!doc || (ft_strlen(doc) > 0 && doc[ft_strlen(doc) - 1] == '\n'
// 				&& ft_strncmp(doc, av[2], ft_strlen(av[2])) == 0
// 				&& ft_strlen(av[2]) == ft_strlen(doc) - 1))
// 		{
// 			if (doc)
// 			{
// 				free(doc);
// 				get_next_line(-1);
// 			}
// 			close(fd[1]);
// 			exit(EXIT_SUCCESS);
// 		}
// 		ft_printf(fd[1], "%s", doc);
// 		free(doc);
// 		ft_printf(1, "pipex here_doc >: ");
// 	}
// }

// void	pipe_here_doc(t_data *data, char **av)
// {
// 	int		fd[2];
// 	pid_t	pid;

// 	if (pipe(fd) == -1)
// 	{
// 		perror("here_doc: pipe");
// 		exit(EXIT_FAILURE);
// 	}
// 	pid = fork();
// 	if (pid == -1)
// 	{
// 		ft_close_fd(fd);
// 		perror("here_doc: fork");
// 		exit(EXIT_FAILURE);
// 	}
// 	if (pid == 0)
// 		read_here_doc(data, av, fd);
// 	else
// 	{
// 		wait(NULL);
// 		dup2(fd[0], STDIN_FILENO);
// 		ft_close_fd(fd);
// 	}
// }
