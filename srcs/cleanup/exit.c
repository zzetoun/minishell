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

#include "../include/minishell.h"

void	exit_full(t_data *data, int exit_num)
{
	if (data)
	{
		if (data->cmd && data->cmd->io_fds)
			ft_close_fds(data->cmd, 1);
		ft_freedom(data, 1);
	}
	exit(exit_num);
}
