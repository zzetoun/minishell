#include "../../include//minishell.h"

void	clear_cmd(t_command **lst, void (*del)(void *))
{
	t_command	*next;
	t_command	*slst;

	next = NULL;
	slst = *lst;
	while (*lst != NULL)
	{
		next = (*lst)->next;
		if (slst->command)
			(*del)(slst->command);
		if (slst->args)
			ft_free_array(slst->args);
		if (slst->pipe_fd)
			(*del)(slst->pipe_fd);
		if (slst->io_fds)
			ft_free_io(slst->io_fds);
		(*del)(slst);
		*lst = next;
	}
	*lst = NULL; // TODO ask george
}