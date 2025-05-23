/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzetoun <zzetoun@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 19:03:45 by zzetoun           #+#    #+#             */
/*   Updated: 2025/05/23 14:16:24 by zzetoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void echo_var_prnt(t_env_info *env, char *arg)
{
	if (arg && *arg && *arg == '?')
		ft_printf(1, "%d", errno);
	else if (arg && *arg && !env_key(env, arg))
		ft_printf(1, "%s", get_env(env, arg));
}
	
static void	echo_s_prnt(char *arg)
{
	while (arg && *arg)
	{
		if (*arg != '\'')
			ft_printf(1, "%c", *arg);
		arg++;
	}
}

static void	echo_prnt(t_env_info *env, char *arg)
{
	if (*arg == '\'')
		return (echo_s_prnt(++arg));
	else if (*arg == '$')
		return (echo_var_prnt(env, ++arg));
	else
		return (echo_s_prnt(arg));
}

int	ft_echo(t_env_info *env, char **args)
{
	char	*new_line;

	new_line = NULL;
	if (args && *args && str_compare(*args, "-n"))
		new_line = *args;
	else
		new_line = NULL;
	while (args && *args)
	{
		echo_prnt(env, *args);
		args++;
	}
	if (!new_line)
		ft_printf(1, "\n");
	return (0);
}
