/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzetoun <zzetoun@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 14:32:53 by zzetoun           #+#    #+#             */
/*   Updated: 2025/04/23 00:02:16 by zzetoun          ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../include/minishell.h"

// static void	update_wds(t_data *data, char *wd, t_env_info *env)
// {
// 	set_env_var(data, "OLDPWD", get_env_var_value(env, "PWD"));
// 	set_env_var(data, "PWD", wd);
// 	if (data->old_working_dir && data->working_dir)
// 	{
// 		free(data->old_working_dir);
// 		data->old_working_dir = ft_strdup(data->working_dir);
// 	}
// 	if (data->working_dir)
// 	{
// 		free(data->working_dir);
// 		data->working_dir = ft_strdup(wd);
// 	}
// 	free(wd);
// }

// static	int	chdir_errno_mod(char *path)
// {
// 	if (errno == ESTALE)
// 		errno = ENOENT;
// 	errmsg_cmd("cd", path, strerror(errno), errno);
// 	return (0);
// }

static int	change_dir(t_data *data, char *path, t_env_info *env)
{
	char	*wd;
	char	buff[PATH_MAX];
	(void)	env;

	wd = NULL;
	ft_printf(1, "path=%s\n", path);
    if (access(path, R_OK) == -1)
        return (perror("[01]Minishell"), 0);
	if (chdir(path) != 0)
		return (perror("[02]Minishell"), 0);
	wd = getcwd(buff, PATH_MAX);
	if (!wd)
	{
		perror("Minishell");
		wd = ft_strjoin(data->working_dir, "/");
		wd = ft_strjoin_free(wd, path);
	}
	else
		wd = ft_strdup(buff);
	//update_wds(data, wd, env);
	return (1);
}

int	ft_cd(t_data *data, char **args, t_env_info *env)
{
	char	*path;

	if (!args || !args[0] || ft_isspace(args[0][0])
		|| args[0][0] == '\0' || str_compare(args[0], "--"))
	{
		ft_printf(1, "I am here[01] \n");
		path = get_env_value(env, "HOME");
		path = ft_substr(path, ft_strlen("HOME="), ft_strlen(path) - 5);
		if (!path || *path == '\0' || ft_isspace(*path))
			return (errmsg_cmd("cd", NULL, "HOME not set", EXIT_FAILURE));
		return (!change_dir(data, path, env));
	}
	if (args[1])
		return (errmsg_cmd("cd", NULL, "too many arguments", EXIT_FAILURE));
	if (str_compare(args[0], "-"))
	{
		ft_printf(1, "I am here[02] \n");
		path = get_env_value(env, "OLDPWD");
		path = ft_substr(path, ft_strlen("OLDPWD="), ft_strlen(path) - 7);
		if (!path)
			return (errmsg_cmd("cd", NULL, "OLDPWD not set", EXIT_FAILURE));
		return (!change_dir(data, path, env));
	}
	return (!change_dir(data, args[1], env));
}
