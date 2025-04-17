/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controllers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzetoun <zzetoun@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 17:07:31 by zzetoun           #+#    #+#             */
/*   Updated: 2025/04/17 20:27:58 by zzetoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	add_detail_quotes(char *cmd)
{
	if (ft_strncmp(cmd, "export", 7) == 0
		|| ft_strncmp(cmd, "unset", 6) == 0)
		return (1);
	return (0);
}

int	errmsg_cmd(char *cmd, char *detail, char *error, int error_numb)
{
	{
		if (cmd != NULL)
			ft_printf(2, "minishell: %s: %s\n", cmd, error);
		if (detail != NULL)
		{
			if (add_detail_quotes(cmd) == 1)
				ft_printf(2, "minishell: '%s': %s\n", detail, error);
			else
				ft_printf(2, "minishell: %s: %s\n", detail, error);
		}
		return (error_numb);
	}
}

void	errmsg(char *error, char *detail, int quotes)
{
	if (quotes)
		ft_printf(2, "minishell:  `%s' %s\n", error, detail);
	else
		ft_printf(2, "minishell: %s: %s\n", error, detail);
}

// void	exit_error(int option, char **array, char *error)
// {
// 	ft_free_array(array);
// 	ft_prnt_error(option, error);
// }

// void	ft_prnt_error(int option, char *error)
// {
// 	if (option == 1)
// 		perror(error);
// 	else
// 		ft_printf(2, "%s\n", error);
// 	exit(EXIT_FAILURE);
// }
