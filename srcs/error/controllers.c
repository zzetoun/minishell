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

/* errmsg:
*	Prints an error message to the standard error, prefixed with the
*	program name, for all cases
*	Returns with the specified error number.
*/
int	errmsg(char *cmd, char *detail, char *error, int err_nb)
{
	if (detail && cmd)
	{
		if (str_compare(cmd, "export") || str_compare(cmd, "unset"))
			ft_printf(2, "-Minishell: %s: `%s': %s\n", cmd, detail, error);
		else if (!str_compare(detail, "quotes"))
			ft_printf(2, "-Minishell: %s: %s: %s\n", cmd, detail, error);
		else
			ft_printf(2, "-Minishell: %s `%s'\n", cmd, error);
	}
	else if (cmd)
		ft_printf(2, "-Minishell: %s: %s\n", cmd, error);
	else
		ft_printf(2, "-Minishell: %s \n", error);
	return (err_nb);
}

/* how_to_message:
*	Prints a how_to message. Used if start-up arguments are invalid.
*/
bool	how_to_message(bool return_val)
{
	ft_printf(2, "Usage: ./minishell\n");
	ft_printf(2, "Usage: ./minishell -c \"input line\"\n");
	return (return_val);
}
