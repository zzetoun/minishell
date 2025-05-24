/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzetoun <zzetoun@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 13:46:55 by zzetoun           #+#    #+#             */
/*   Updated: 2025/05/08 13:46:55 by zzetoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static char	*find_path(t_env_info *env)
{
	int		i;
	char	**paths;
	char	*path;

	i = -1;
	paths = ft_split(get_env(env, "PATH"), ':');
	if (!paths)
		return (NULL);
	while (paths[++i])
	{
		path = ft_strjoin(paths[i], "/");
		if (!path)
			return (ft_free_array(paths), NULL);
		path = ft_strjoin_free(path, "env");
		if (!path)
			return (ft_free_array(paths), NULL);
		if (access(path, F_OK) == 0)
			return (ft_free_array(paths), path);
		free(path);
	}
	ft_free_array(paths);
	return (NULL);
}

int	ft_env(t_env_info *env, char **args, size_t idx)
{
	char	**envp;
	char	*path;
	ft_printf(1, "I enter env\n");
	if (args)
		return (errmsg("env", NULL, ARGERR0R, EXIT_FAILURE));
	if (get_env(env, "PATH"))
	{
		envp = env_tostr(env);
		if (!envp)
			return (errmsg("malloc", NULL, MALLERR, EXIT_FAILURE));
		path = find_path(env);
		while (path && envp[++idx])
			ft_printf(1, "%s\n", envp[idx]);
		ft_free_array(envp);
		if (!path)
			return (errmsg("env", NULL, "command not found", CMD_NOT_FOUND));
		free(path);
	}
	else
		return (errmsg("env", NULL, "No such file or directory", CMD_NOT_FOUND));
	return (EXIT_SUCCESS);
}
