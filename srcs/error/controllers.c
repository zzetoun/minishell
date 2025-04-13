/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controllers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzetoun <zzetoun@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 17:07:31 by zzetoun           #+#    #+#             */
/*   Updated: 2025/04/13 21:08:48 by zzetoun          ###   ########.fr       */
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
		char	*msg;
	
		msg = ft_strdup("minishell: ");
		if (cmd != NULL)
		{
			msg = ft_strjoin(msg, cmd);
			msg = ft_strjoin(msg, ": ");
		}
		if (detail != NULL)
		{
			if (add_detail_quotes(cmd))
				msg = ft_strjoin(msg, "`");
			msg = ft_strjoin(msg, detail);
			if (add_detail_quotes(cmd))
				msg = ft_strjoin(msg, "'");
			msg = ft_strjoin(msg, ": ");
		}
		msg = ft_strjoin(msg, error);
		ft_printf(2, "%s\n", msg);
		free(msg);
		return (error_numb);
	}
}
void	errmsg(char *error, char *detail, int quotes)
{
	char	*msg;

	msg = ft_strdup("minishell: ");
	msg = ft_strjoin(msg, error);
	if (quotes)
		msg = ft_strjoin(msg, " `");
	else
		msg = ft_strjoin(msg, ": ");
	msg = ft_strjoin(msg, detail);
	if (quotes)
		msg = ft_strjoin(msg, "'");
	ft_printf(2, "%s\n", msg);
	free(msg);
}

void	exit_error(int option, char **array, char *error)
{
	ft_free_array(array);
	ft_prnt_error(option, error);
}

void	ft_prnt_error(int option, char *error)
{
	if (option == 1)
		perror(error);
	else
		ft_printf(2, "%s\n", error);
	exit(EXIT_FAILURE);
}

