/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzetoun <zzetoun@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 14:32:53 by zzetoun           #+#    #+#             */
/*   Updated: 2025/04/21 18:32:06 by zzetoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// static void	update_wds(t_data *data, char *wd)
// {
// 	set_env_var(data, OLDPWD, get_env_var_value(data->env, "PWD"));
// 	set_env_var(data, "PWD", wd);
// 	if (data->old_working_dir)
// 	{
// 		ft_free_ptr(data->old_working_dir);
// 		data->old_working_dir = ft_strdup(data->working_dir);
// 	}
// 	if (data->working_dir)
// 	{
// 		ft_free_ptr(data->working_dir);
// 		data->working_dir = ft_strdup(wd);
// 	}
// 	ft_free_ptr(wd);
// }

// static	int	chdir_errno_mod(char *path)
// {
// 	if (errno == ESTALE)
// 		errno = ENOENT;
// 	errmsg_cmd(CD, path, strerror(errno), errno);
// 	return (0);
// }

// static int	change_dir(t_data *data, char *path)
// {
// 	char	*wd;
// 	char	buff[PATH_MAX];

// 	wd = NULL;
//     if (access(path, R_OK) == -1)
//         return (perror("Minishell"), 0);
// 	if (chdir(path) != 0)
// 		return (perror("Minishell"), 0);
// 	wd = getcwd(buff, PATH_MAX);
// 	if (!wd)
// 	{
// 		perror("Minishell");
// 		wd = ft_strjoin(data->working_dir, "/");
// 		wd = ft_strjoin_free(wd, path);
// 	}
// 	else
// 		wd = ft_strdup(buff);
// 	update_wds(data, wd);
// 	return (1);
// }

// int	ft_cd(t_data *data, char **args)
// {
// 	char	*path;

// 	if (!args || !args[1] || ft_isspace(args[1][0])
// 		|| args[1][0] == '\0' || str_compare(args[1], "--"))
// 	{
// 		path = get_env_var_value(data->env, "HOME");
// 		if (!path || *path == '\0' || ft_isspace(*path))
// 			return (errmsg_cmd(CD, NULL, "HOME not set", EXIT_FAILURE));
// 		return (!change_dir(data, path));
// 	}
// 	if (args[2])
// 		return (errmsg_cmd(CD, NULL, "too many arguments", EXIT_FAILURE));
// 	if (str_compare(args[1], "-"))
// 	{
// 		path = get_env_var_value(data->env, OLDPWD);
// 		if (!path)
// 			return (errmsg_cmd(CD, NULL, "OLDPWD not set", EXIT_FAILURE));
// 		return (!change_dir(data, path));
// 	}
// 	return (!change_dir(data, args[1]));
// }
