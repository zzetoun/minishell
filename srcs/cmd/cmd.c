/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzetoun <zzetoun@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 17:28:34 by zzetoun           #+#    #+#             */
/*   Updated: 2025/04/13 18:16:55 by zzetoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	execute_cmd(t_data *data, t_command *cmd)
{
	int	ret;

	ret = CMDER;
	if (ft_strncmp(cmd->command, "cd", 3) == 0)
		ret = ft_cd(data, cmd->args);
	else if (ft_strncmp(cmd->command, "echo", 5) == 0)
		ret = ft_echo(data, cmd->args);
	else if (ft_strncmp(cmd->command, "env", 4) == 0)
		ret = ft_env(data, cmd->args);
	else if (ft_strncmp(cmd->command, "export", 7) == 0)
		ret = export_builtin(data, cmd->args);
	else if (ft_strncmp(cmd->command, "pwd", 4) == 0)
		ret = ft_pwd(data);
	else if (ft_strncmp(cmd->command, "unset", 6) == 0)
		ret = ft_unset(data, cmd->args);
	else if (ft_strncmp(cmd->command, "exit", 5) == 0)
		ret = ft_exit(data, cmd->args);
	return (ret);
}