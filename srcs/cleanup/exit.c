/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzetoun <zzetoun@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 20:10:39 by zzetoun           #+#    #+#             */
/*   Updated: 2025/06/01 17:59:24 by zzetoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	exit_full(t_data *data, int exit_num)
{
	if (data)
	{
		if (data->cmd && data->cmd->io_fds)
			ft_close_fds(data->cmd, true);
		ft_freedom(data, 1);
	}
	exit(exit_num);
}
