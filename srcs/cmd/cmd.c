/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzetoun <zzetoun@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 17:28:34 by zzetoun           #+#    #+#             */
/*   Updated: 2025/04/16 20:32:48 by zzetoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// int	execute_cmd(t_data *data, t_command *cmd)
// {
// 	int	value;

// 	value = CMD_NOT_FOUND;
// 	if (ft_strncmp(cmd->command, "cd", 3) == 0)
// 		value = ft_cd(data, cmd->args);
// 	else if (ft_strncmp(cmd->command, "echo", 5) == 0)
// 		value = ft_echo(data, cmd->args);
// 	else if (ft_strncmp(cmd->command, "env", 4) == 0)
// 		value = ft_env(data, cmd->args);
// 	else if (ft_strncmp(cmd->command, "export", 7) == 0)
// 		value = ft_export(data, cmd->args);
// 	else if (ft_strncmp(cmd->command, "pwd", 4) == 0)
// 		value = ft_pwd(data);
// 	else if (ft_strncmp(cmd->command, "unset", 6) == 0)
// 		value = ft_unset(data, cmd->args);
// 	else if (ft_strncmp(cmd->command, "exit", 5) == 0)
// 		value = ft_exit(data, cmd->args);
// 	return (value);
// }
