/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzetoun <zzetoun@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 19:03:45 by zzetoun           #+#    #+#             */
/*   Updated: 2025/05/11 20:40:58 by zzetoun          ###   ########.fr       */
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

static void	echo_d_prnt(t_env_info *env, char *arg)
{
	char	*var_head;

	var_head = NULL;
	while (arg && *arg)
	{
		if (arg && *arg == '$')
		{
			var_head = ++arg;
			if (!env_key(env, arg))
				echo_var_prnt(env, arg);
			// else
			// {
			// 	while (arg && *arg && !ft_isalnum(*arg))
			// 		arg++;
				
			// }
		}
		else
			ft_printf(1, "%c", *arg);
		if (arg && *arg)
			arg++;
	}
}
	
static void	echo_s_prnt(char *arg)
{
	while (arg && *arg)
	{
		if (arg && *arg && *arg != '\'')
			ft_printf(1, "%c", *arg);
		arg++;
	}
}

static void	echo_prnt(t_env_info *env, char *arg)
{
	if (arg && *arg && *arg == '\'')
		return (echo_s_prnt(arg));
	if (arg && *arg && *arg == '\"')
		return (echo_d_prnt(env, arg));
	if (arg && *arg && *arg == '$')
		return (echo_var_prnt(env, arg));
}

int	ft_echo(t_env_info *env, char **args)
{
	char	*arg;
	char	*new_line;

	new_line = NULL;
	if (args && *args)
	{
		new_line = *args;
		while (args && *args)
		{
			arg = *args;
			echo_prnt(env, arg);
			args++;
		}
	}
	if (new_line && *new_line && !str_compare(new_line, "-n"))
		ft_printf(1, "\n");
	return (0);
}
