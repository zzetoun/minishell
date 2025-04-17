/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzetoun <zzetoun@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 18:10:58 by zzetoun           #+#    #+#             */
/*   Updated: 2025/04/17 21:43:20 by zzetoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int ft_pwd(t_data *data)
{
	char	buf[PATH_MAX];
	char	*cwd;

	if (data->working_dir)
	{
		ft_printf(1, "%s\n", data->working_dir);
		return (EXIT_SUCCESS);
	}
	cwd = getcwd(buf, PATH_MAX);
	if (cwd)
	{
		ft_printf(1, "%s\n", cwd);
		return (EXIT_SUCCESS);
	}
	perror("pwd ERROR");
	return (EXIT_FAILURE);
}
