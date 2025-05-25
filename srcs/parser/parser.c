/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzetoun <zzetoun@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 16:59:14 by zzetoun           #+#    #+#             */
/*   Updated: 2025/05/25 20:15:06 by zzetoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

bool	cmd_args_split(t_data *data, char *input)
{
	char	*args;
	int	 idx;

	add_back_cmd(&data->cmd, add_new_cmd(false));
	setup_io(data->cmd);
	args = ft_strchr(input, ' ');
	ft_printf(1, "args: {%s}\n", args);
	data->cmd->command = ft_substr(input, 0, ft_strlen(input) - ft_strlen(args));
	ft_printf(1, "cmd: {%s}\n", data->cmd->command);
	data->cmd->args = ft_split(input, ' ');
	idx = -1;
	while (data->cmd->args && data->cmd->args[++idx])
		ft_printf(1, "arg[%d]= {%s}\n", idx, data->cmd->args[idx]);
	return (true);
}
