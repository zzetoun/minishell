/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzetoun <zzetoun@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 22:47:26 by zzetoun           #+#    #+#             */
/*   Updated: 2025/05/06 22:47:26 by zzetoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	update_wds(t_data *data, char *wd, t_env_info *env)
{
	set_env(env, "OLDPWD", get_env(env, "PWD"));
	set_env(env, "PWD", wd);
	if (data->old_working_dir)
	{
		free(data->old_working_dir);
		data->old_working_dir = ft_strdup(data->working_dir);
	}
	if (data->working_dir)
	{
		free(data->working_dir);
		data->working_dir = ft_strdup(wd);
	}
	ft_free_ptr(wd);
}

static int	change_dir(t_data *data, char *path, t_env_info *env)
{
	char	*wd;
	char	buff[PATH_MAX];

	wd = NULL;
	if (chdir(path) == -1)
	{
		if (errno == ESTALE)
			errno = ENOENT;
		return (errmsg("cd", path, strerror(errno), errno));
	}
	wd = getcwd(buff, PATH_MAX);
	if (!wd)
	{
		errmsg(CDERROR, GETCWDE, strerror(errno), errno);
		wd = ft_strjoin(data->working_dir, "/");
		wd = ft_strjoin_free(wd, path);
	}
	else
		wd = ft_strdup(buff);
	update_wds(data, wd, env);
	return (1);
}

int	ft_cd(t_data *data, char **args, t_env_info *env)
{
	char	*path;

	if (!args || !args[1] || ft_isspace(args[1][0])
		|| args[1][0] == '\0' || str_compare(args[1], "--")
		|| str_compare(args[1], "~"))
	{
		path = get_env(env, "HOME");
		if (!path || *path == '\0' || ft_isspace(*path))
			return (errmsg("cd", NULL, "HOME not set", EXIT_FAILURE));
		return (!change_dir(data, path, env));
	}
	if (args[2])
		return (errmsg("cd", NULL, ARGERR0R, EXIT_FAILURE));
	if (str_compare(args[1], "-"))
	{
		path = get_env(env, "OLDPWD");
		if (!path)
			return (errmsg("cd", NULL, "OLDPWD not set", EXIT_FAILURE));
		else if (chdir(path) == 0)
			ft_printf(1, "%s\n", path);
		return (!change_dir(data, path, env));
	}
	return (!change_dir(data, args[1], env));
}
