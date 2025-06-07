<<<<<<< HEAD
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_darray_to_str.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzetoun <zzetoun@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 18:14:03 by zzetoun           #+#    #+#             */
/*   Updated: 2025/06/03 15:17:21 by zzetoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_darray_to_str(char **darray, char *seperator)
{
	char	*str;
	int		idx;

	if (!darray || !*darray)
		return (NULL);
	idx = -1;
	str = NULL;
	while (darray[++idx])
	{
		if (idx == 0)
			str = ft_strdup(darray[idx]);
		else
			str = ft_strjoin_free(str, darray[idx]);
		if (darray[idx + 1])
			str = ft_strjoin_free(str, seperator);
	}
	return (str);
}
=======
<<<<<<<< HEAD:srcs/utils/libft/ft_darray_to_str.c
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_darray_to_str.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzetoun <zzetoun@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 18:14:03 by zzetoun           #+#    #+#             */
/*   Updated: 2025/05/07 18:14:07 by zzetoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_darray_to_str(char **darray, char *seperator)
{
	char	*str;
	int		idx;

	if (!darray || !*darray)
		return (NULL);
	idx = -1;
	str = NULL;
	while (darray[++idx])
	{
		if (idx == 0)
			str = ft_strdup(darray[idx]);
		else
			str = ft_strjoin_free(str, darray[idx]);
		if (darray[idx + 1])
			str = ft_strjoin_free(str, seperator);
	}
	return (str);
}
========
/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_util_clean.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzetoun <zzetoun@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 15:48:26 by zzetoun           #+#    #+#             */
/*   Updated: 2025/06/04 03:22:45 by zzetoun          ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../include/minishell.h"

void	clear_cmd(t_command **list, void (*del)(void *))
{
	t_command	*next;

	next = NULL;
	while (*list)
	{
		next = (*list)->next;
		if ((*list)->command)
			(*del)((*list)->command);
		if ((*list)->args)
			ft_free_array((*list)->args);
		if ((*list)->pipe_fd)
			(*del)((*list)->pipe_fd);
		if ((*list)->io_fds)
			ft_free_io((*list)->io_fds);
		(*del)(*list);
		*list = next;
	}
}
>>>>>>>> minishell_final:srcs/parser/cmd_util_clean.c
>>>>>>> minishell_final
