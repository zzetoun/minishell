/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzetoun <zzetoun@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 16:43:45 by zzetoun           #+#    #+#             */
/*   Updated: 2025/05/08 16:43:45 by zzetoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	str_compare(char const *s1, char const *s2)
{
	int	result;

	if (!s1 || !s2)
		return (errmsg_cmd(NULL, "Compare Error: strings NULL", NULL, 1));
	result = (!ft_strncmp(s1, s2, ft_strlen(s2)));
	result *= (ft_strlen(s1) == strlen(s2));
	return (result);
}

int	execute_cmd(t_data *data, t_command *cmd, t_env_info *env)
{
	int	value;

	value = CMD_NOT_FOUND;
	if (str_compare(cmd->command, "pwd"))
		value = ft_pwd(data);
	else if (str_compare(cmd->command, "cd"))
		value = ft_cd(data, cmd->args, env);
	else if (str_compare(cmd->command, "export"))
		value = ft_export(env, cmd->args);
	else if (str_compare(cmd->command, "unset"))
		value = ft_unset(env, cmd->args);
	else if (str_compare(cmd->command, "env"))
		value = ft_env(env, cmd->args, -1);
	return (value);
}
