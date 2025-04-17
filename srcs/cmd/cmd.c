/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzetoun <zzetoun@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 17:28:34 by zzetoun           #+#    #+#             */
/*   Updated: 2025/04/17 21:35:17 by zzetoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int str_compare(char *s1, char *s2)
{
    int result;

	if (!s1 || !s2)
	{
		ft_printf(1, "Minishell ERROR: string is NULL\n");
		return (0);
	}
    result = (ft_strncmp(s1, s2, ft_strlen(s1)) == 0);
    result *= (ft_strlen(s1) == strlen(s2));	
    return (result);
}

int	execute_cmd(t_data *data, t_command *cmd)
{
	int	value;

	value = CMD_NOT_FOUND;
	if (str_compare(cmd->command, "pwd") == 1)
		value = ft_pwd(data);
	return (value);
}
