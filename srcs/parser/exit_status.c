/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_status.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzetoun <zzetoun@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 01:18:40 by igorsergeev       #+#    #+#             */
/*   Updated: 2025/06/07 18:14:03 by zzetoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//TODO setuping only here last status of the command for current command struct

/**
 * @brief funtionc
 * @param cmd
 * @param last_exit_code
 */
void	setup_last_exit_code(t_command *cmd, int last_exit_code)
{
	t_command	*tmp;
	size_t		i;
	char		*new;

	if (!cmd)
		return ;
	tmp = cmd;
	while (tmp)
	{
		i = (size_t) - 1;
		tmp->command = ft_replace_substr(tmp->command, "$?",
				ft_itoa(last_exit_code));
		while (tmp->args && tmp->args[i++])
		{
			if (!tmp->args[i])
				continue ;
			if (strstr(tmp->args[i], "$?"))
			{
				new = ft_replace_substr(tmp->args[i], "$?",
						ft_itoa(last_exit_code));
				free(tmp->args[i]);
				tmp->args[i] = new;
			}
		}
		tmp = tmp->next;
	}
}
