/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igorsergeevic <igorsergeevic@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 01:08:09 by igorsergeev       #+#    #+#             */
/*   Updated: 2025/06/07 01:09:46 by igorsergeev      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser.h"
//TODO change to ft_free_array
void	free_split(char **split)
{
	size_t	i;

	if (!split || !*split)
		return ;
	i = 0;
	while (split[i])
		free(split[i++]);
	free(split);
}

static void	*free_and_return_null(char **str)
{
	if (str && *str)
	{
		free(*str);
		*str = NULL;
	}
	return (NULL);
}

//TODO make size for it - 25 lines
char	**append_arg(char **args, const char *arg)
{
	size_t	i;
	char	**new_args;
	size_t	j;

	if (!args)
	{
		new_args = malloc(sizeof(char *) * 2);
		if (!new_args)
			return (NULL);
		new_args[0] = ft_strdup(arg);
		if (!new_args[0])
			return (free_and_return_null(&new_args[0]));
		new_args[1] = NULL;
		return (new_args);
	}
	i = 0;
	while (args[i])
		i++;
	new_args = malloc(sizeof(char *) * (i + 2));
	if (!new_args)
		return (NULL);
	j = 0;
	while (j < i)
	{
		new_args[j] = args[j];
		j++;
	}
	new_args[i] = ft_strdup(arg);
	if (!new_args[i])
		return (free_and_return_null(&new_args[0]));
	new_args[i + 1] = NULL;
	free(args);
	return (new_args);
}

t_command	*get_last_cmd(t_command *cmd)
{
	while (cmd && cmd->next)
		cmd = cmd->next;
	return (cmd);
}
