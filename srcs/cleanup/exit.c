/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzetoun <zzetoun@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 20:10:39 by zzetoun           #+#    #+#             */
/*   Updated: 2025/05/23 20:42:10 by zzetoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	exit_full(t_data *data, int exit_num)
{

	if (data)
	{
        //printf("command=[%s] i am inside exit full\n", data->cmd->command);
		if (data->user_input)
			ft_free_dptr((void *)&data->user_input);
		if (data->cmd && data->cmd->io_fds)
			ft_close_fds(data->cmd, 1);
		if (data->cmd)
			clear_cmd(&data->cmd, &ft_free_ptr);
		ft_freedom(&data, 1);
		rl_clear_history();
	}
	exit(exit_num);
}
