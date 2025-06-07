/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   excv_util.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzetoun <zzetoun@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 14:51:57 by zzetoun           #+#    #+#             */
/*   Updated: 2025/06/07 18:19:20 by zzetoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cmd_is_dir(char *cmd)
{
	struct stat	cmd_stat;

	ft_memset(&cmd_stat, 0, sizeof(cmd_stat));
	stat(cmd, &cmd_stat);
	return (S_ISDIR(cmd_stat.st_mode));
}

int	check_cmd_not_found(t_data *data, t_command *cmd)
{
	if (!ft_strchr(cmd->command, '/') && get_env(data->env, "PATH"))
		return (errmsg(cmd->command, NULL, CMDERR01, CMD_NOT_FOUND));
	if (access(cmd->command, F_OK) != 0)
		return (errmsg(cmd->command, NULL, strerror(errno), CMD_NOT_FOUND));
	else if (cmd_is_dir(cmd->command))
		return (errmsg(cmd->command, NULL, CMDERR02, CMD_NOT_EXECU));
	else if (access(cmd->command, F_OK | X_OK) != 0)
		return (errmsg(cmd->command, NULL, strerror(errno), CMD_NOT_EXECU));
	return (EXIT_SUCCESS);
}
