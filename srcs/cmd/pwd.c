/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzetoun <zzetoun@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 18:10:58 by zzetoun           #+#    #+#             */
/*   Updated: 2025/04/21 20:36:27 by zzetoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int ft_pwd(t_data *data)
{
	int	idx;

	idx = 0;
	if (data->working_dir)
	{
		free(data->working_dir);
		ft_printf(1, "how many times I enter here?\n");
	}
	while(data->env[idx] && ft_strncmp(data->env[idx], "PWD", 3) != 0)
		idx++;
	data->working_dir = ft_substr(data->env[idx], ft_strlen("PWD="), -1);
	if (data->working_dir)
	{
		ft_printf(1, "%s\n", data->working_dir);
		return (EXIT_SUCCESS);
	}
	errmsg_cmd(PWD, NULL, strerror(errno), errno);
	return (EXIT_FAILURE);
}
