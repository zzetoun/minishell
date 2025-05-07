/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controllers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzetoun <zzetoun@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 18:31:14 by zzetoun           #+#    #+#             */
/*   Updated: 2025/05/07 18:31:14 by zzetoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	errmsg_cmd(char *cmd, char *detail, char *errmsg, int err_nb)
{
	if (detail && cmd)
	{
		if (str_compare(cmd, "export") || str_compare(cmd, "unset"))
			ft_printf(2, "-Minishell: %s: `%s': %s\n", cmd, detail, errmsg);
		else
			ft_printf(2, "-Minishell: %s: %s: %s\n", cmd, detail, errmsg);
	}
	else if (cmd)
		ft_printf(2, "-Minishell: %s: %s\n", cmd, errmsg);
	else
		ft_printf(2, "-Minishell: %s \n", errmsg);
	return (err_nb);
	
}

void	errmsg(char *error, char *detail, int quotes)
{
	if (quotes)
		ft_printf(2, "minishell:  `%s' %s\n", error, detail);
	else
		ft_printf(2, "minishell: %s: %s\n", error, detail);
}

// void	exit_error(int	option, char **array, char *error)
// {
// 	ft_free_array(array);
// 	ft_prnt_error(option, error);
// }

// void	ft_prnt_error(int	option, char *error)
// {
// 	if (option == 1)
// 		perror(error);
// 	else
// 		ft_printf(2, "%s\n", error);
// 	exit(EXIT_FAILURE);
// }
