/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzetoun <zzetoun@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 17:28:34 by zzetoun           #+#    #+#             */
/*   Updated: 2025/04/17 16:00:32 by zzetoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int static cmd_compare(char *s1, char *s2)
{
    int result;

    result = ft_strncmp(s1, s2, strlen(s1));
    result *= (ft_strlen(s1) == strlen(s2));
    return (result);
}

int	execute_cmd(t_data *data, t_command *cmd)
{
	int	value;

	value = CMD_NOT_FOUND;
	if (cmd_compare(cmd->command, "pwd") > 0)
		value = ft_pwd(data);
	return (value);
}
