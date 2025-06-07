/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzetoun <zzetoun@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 20:02:19 by zzetoun           #+#    #+#             */
/*   Updated: 2025/06/07 18:43:46 by zzetoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*valid_cmd_path(char *cmd, char **paths)
{
	int		idx;
	char	*path;

	path = NULL;
	idx = -1;
	while (paths[++idx])
	{
		path = ft_strjoin(paths[idx], cmd);
		if (!path)
		{
			errmsg("malloc", NULL, MALLERR, EXIT_FAILURE);
			return (NULL);
		}
		if (access(path, F_OK | X_OK) == 0)
			return (path);
		ft_free_dptr((void **)&path);
	}
	return (NULL);
}

/* get_env_paths:
*	Attempts to extract paths from the PATH environment variable.
*	Returns an array of paths on success. On failure, returns NULL.
*/
static char	**get_env_paths(t_data *data)
{
	char	**paths;

	if (!get_env(data->env, "PATH"))
		return (NULL);
	paths = ft_split(get_env(data->env, "PATH"), ':');
	if (!paths)
		return (NULL);
	return (paths);
}

/* get_cmd_path:
*	Searches the PATH environment variable for the location of the given
*	command's binary file.
*	Returns the path to the command binary file. NULL if no valid path
*	is found.
*/
char	*get_cmd_path(t_data *data, char *name)
{
	char	**env_paths;
	char	*cmd;
	char	*cmd_path;

	if (!name)
		return (NULL);
	env_paths = get_env_paths(data);
	if (!env_paths)
		return (NULL);
	cmd = ft_strjoin("/", name);
	if (!cmd)
	{
		ft_free_array(env_paths);
		return (NULL);
	}
	cmd_path = valid_cmd_path(cmd, env_paths);
	free(cmd);
	ft_free_array(env_paths);
	if (!cmd_path)
		return (NULL);
	return (cmd_path);
}
