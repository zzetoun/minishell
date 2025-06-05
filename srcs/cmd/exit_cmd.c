/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzetoun <zzetoun@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 22:49:06 by zzetoun           #+#    #+#             */
/*   Updated: 2025/06/03 19:52:06 by zzetoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	ft_atoi_error(const char *str, bool *error)
{
	unsigned long long	nb;
	int					sign;

	nb = 0;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	sign = 1 - 2 * (*str == '-');
	str += (*str == '-' || *str == '+');
	while (*str >= '0' && *str <= '9')
		nb = (10 * nb) + *(str++) - '0';
	if ((nb >= LLONG_MAX && sign == -1) || nb >= LLONG_MAX)
		(*error) = true;
	return ((int)nb * sign);
}

static int	get_exit_code(char *arg, bool *error)
{
	unsigned long long	idx;

	if (!arg)
		return (g_final_exit_code);
	idx = 0;
	while (ft_isspace(arg[idx]))
		idx++;
	if (arg[idx] == '\0')
		(*error) = true;
	idx += (arg[idx] == '-' || arg[idx] == '+');
	if (!ft_isdigit(arg[idx]))
		(*error) = true;
	while (arg[idx])
	{
		if (!ft_isdigit(arg[idx]) && !ft_isspace(arg[idx]))
			(*error) = true;
		idx++;
	}
	idx = ft_atoi_error(arg, error);
	return (idx % 256);
}

/* silent_exit_check:
*	If exit is not called alone, it should not print "exit".
*	Returns true if exit should not be printed. False if exit was called
*	alone and the "exit" message should be printed.
*/
static bool	silent_exit_check(t_data *data)
{
	t_command	*cmd;

	cmd = data->cmd;
	if (!cmd)
		return (false);
	if (cmd->next != NULL || cmd->prev != NULL)
		return (true);
	return (false);
}

/* ft_exit:
*	Executes the exit builtin.
*	If alone, prints exit and exits the shell with the provided exit code, or 0.
*	If piped, exits the child process with the provided exit code and 
*	does not exit
*	minishell.
*	In case of failure due to invalid arguments, does not exit the shell
*	and returns an error exit code (1 or 2) instead.
*/
int	ft_exit(t_data *data, char **args)
{
	int		exit_code;
	bool	error;

	error = false;
	if (!silent_exit_check(data) && data->interactive)
		ft_printf(2, "exit\n");
	if (!args || !args[1])
		exit_code = g_final_exit_code;
	else
	{
		exit_code = get_exit_code(args[1], &error);
		if (error)
			exit_code = errmsg("exit", args[1], EXITRR01, 255);
		else if (args[2])
			return (errmsg("exit", NULL, EXITRR02, 1));
	}
	exit_full(data, exit_code);
	return (2);
}
