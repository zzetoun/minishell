/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzetoun <zzetoun@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 20:02:19 by zzetoun           #+#    #+#             */
/*   Updated: 2025/05/23 20:06:58 by zzetoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static char	*find_valid_cmd_path(char *cmd, char **paths)
{
	int		idx;
	char	*cmd_path;

	cmd_path = NULL;
	idx = -1;
	while (paths[++idx])
	{
		cmd_path = ft_strjoin(paths[idx], cmd);
		if (!cmd_path)
		{
			errmsg("malloc", NULL, MALLERR, EXIT_FAILURE);
			return (NULL);
		}
		if (access(cmd_path, F_OK | X_OK) == 0)
			return (cmd_path);
		ft_free_ptr(cmd_path);
	}
	return (NULL);
}

/* get_paths_from_env:
*	Attempts to extract paths from the PATH environment variable.
*	Returns an array of paths on success. On failure, returns NULL.
*/
static char	**get_paths_from_env(t_data *data)
{
	char	**env_paths;

	if (!get_env(data->env, "PATH"))
		return (NULL);
	env_paths = ft_split(get_env(data->env, "PATH"), ':');
	if (!env_paths)
		return (NULL);
	return (env_paths);
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
	env_paths = get_paths_from_env(data);
	if (!env_paths)
		return (NULL);
	cmd = ft_strjoin("/", name);
	if (!cmd)
	{
		ft_free_array(env_paths);
		return (NULL);
	}
	cmd_path = find_valid_cmd_path(cmd, env_paths);
	if (!cmd_path)
	{
		ft_free_ptr(cmd);
		ft_free_array(env_paths);
		return (NULL);
	}
	return (cmd_path);
}
