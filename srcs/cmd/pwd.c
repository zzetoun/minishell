/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzetoun <zzetoun@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 22:57:35 by zzetoun           #+#    #+#             */
/*   Updated: 2025/05/06 22:57:35 by zzetoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(t_data *data)
{
	char	buff[PATH_MAX];

	if (data->working_dir)
	{
		ft_printf(1, "%s\n", data->working_dir);
		return (EXIT_SUCCESS);
	}
	else
	{
		data->working_dir = ft_strdup(getcwd(buff, PATH_MAX));
		if (data->working_dir)
		{
			ft_printf(1, "%s\n", data->working_dir);
			return (EXIT_SUCCESS);
		}
	}
	ft_printf(2, "Minishell: pwd: %s\n", strerror(errno));
	return (errno);
}
