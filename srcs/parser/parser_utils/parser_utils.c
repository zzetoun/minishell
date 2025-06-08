/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzetoun <zzetoun@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 01:08:09 by igorsergeev       #+#    #+#             */
/*   Updated: 2025/06/08 16:13:20 by zzetoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	*free_and_return_null(char **str)
{
	if (str && *str)
	{
		free(*str);
		*str = NULL;
	}
	return (NULL);
}
static char	**setup_args(const char *arg)
{
	char **new_args;

	new_args = ft_calloc(2, sizeof(char *));
	if (!new_args)
		return (NULL);
	new_args[0] = ft_strdup(arg);
	if (!new_args[0])
		return (free_and_return_null(&new_args[0]));
	new_args[1] = NULL;
	return (new_args);
}

char	**append_arg(char **args, const char *arg)
{
	char	**new_args;
	int		len;
	int		idx;

	if (!args)
		return(setup_args(arg));
	len = ft_array_len(args);
	new_args = ft_calloc((len + 2), sizeof(char *));
	if (!new_args)
		return (NULL);
	idx = -1;
	while (++idx < len)
		new_args[idx] = ft_strdup(args[idx]);
	new_args[len] = ft_strdup(arg);
	if (!new_args[len])
		return (free_and_return_null(&new_args[0]));
	new_args[len + 1] = NULL;
	free(args);
	return (new_args);
}

t_command	*get_last_cmd(t_command *cmd)
{
	while (cmd && cmd->next)
		cmd = cmd->next;
	return (cmd);
}
