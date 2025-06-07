/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzetoun <zzetoun@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 13:46:55 by zzetoun           #+#    #+#             */
/*   Updated: 2025/06/08 01:01:25 by zzetoun          ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "minishell.h"

void	free_env(t_env_info *env)
{
	t_envp	*list;

	list = env->head;
	while (list)
	{
		list = list->next;
		env->head->idx = 0;
		free(env->head->str);
		free(env->head->key);
		free(env->head->value);
		free(env->head);
		env->head = list;
	}
	env->size = 0;
}

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

int	ft_env(t_env_info *env, char **args, size_t idx) //TODO fix the error message when PATH unsets
{
	char	**envp;
	char	*path;

	if (args && args[1])
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
			return (CMD_NOT_FOUND);
		free(path);
	}
	else
		return (CMD_NOT_FOUND);
	return (EXIT_SUCCESS);
}
