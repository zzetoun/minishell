/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzetoun <zzetoun@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 19:03:45 by zzetoun           #+#    #+#             */
/*   Updated: 2025/05/24 14:53:37 by zzetoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/* new_line_check:
*	Returns true if arg is a dash followed only by 
*   one or more 'n' chars (e.g. "-n", "-nnn").
*/
static bool	new_line_check(char *arg)
{
	int	idx;

	idx = 0;
	if (arg[idx++] != '-')
		return (false);
	while (arg[idx] && arg[idx] == 'n')
		idx++;
	if (!arg[idx])
		return (true);
	else
		return (false);
}
/* ft_echo:
*	Prints all args separated by spaces and adds a newline unless "-n"
*   flag was first.
*	Supports only the single "-n" style option. Always returns EXIT_SUCCESS.
*	prints space after each args, last one is not printed.
*/
int	ft_echo(char **args)
{
	bool	new_line;
	size_t	array_size;

	new_line = NULL;
	if (args && *args && new_line_check(*args))
	{
		new_line = true;
		args++;
	}
	else
		new_line = false;
	array_size = ft_array_len(args);
	while (args && *args)
	{
		if (array_size > 1)
			ft_printf(1, "%s ", *args);
		else
			ft_printf(1, "%s", *args);
		args++;
		array_size--;
	}
	if (!new_line)
		ft_printf(1, "\n");
	return (EXIT_SUCCESS);
}
