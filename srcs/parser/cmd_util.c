#include "../../include//minishell.h"

void	clear_cmd(t_command **lst, void (*del)(void *))
{
	t_command	*next;

	next = NULL;
	while (*lst != NULL)
	{
		next = (*lst)->next;
		if ((*lst)->command)
			(*del)((*lst)->command);
		if ((*lst)->args)
			ft_free_array((*lst)->args);
		if ((*lst)->pipe_fd)
			(*del)((*lst)->pipe_fd);
//		if ((*lst)->io_fds)
//			ft_free_io((*lst)->io_fds);
		(*del)((*lst));
		*lst = next;
	}
}