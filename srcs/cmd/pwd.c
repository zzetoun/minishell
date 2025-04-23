/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzetoun <zzetoun@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 23:52:57 by zzetoun           #+#    #+#             */
/*   Updated: 2025/04/22 23:53:25 by zzetoun          ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../include/minishell.h"

int ft_pwd(t_data *data)
{
	char	buff[PATH_MAX];

	if (data->working_dir)
	{
		ft_printf(1, "%s\n", data->working_dir);
		return(EXIT_SUCCESS);
	}
	else
	{
		data->working_dir = getcwd(buff, PATH_MAX);
		if (data->working_dir)
		{
			ft_printf(1, "%s\n", data->working_dir);
			return(EXIT_SUCCESS);
		}
	}
	errmsg_cmd(PWD, NULL, strerror(errno), errno);
	return (EXIT_FAILURE);
}
