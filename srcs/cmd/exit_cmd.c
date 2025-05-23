/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzetoun <zzetoun@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 22:49:06 by zzetoun           #+#    #+#             */
/*   Updated: 2025/05/23 20:48:36 by zzetoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	ft_atoi_error(const char *str, int *error)
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
		(*error) = 1;
	return ((int)nb * sign);
}

static int	get_exit_code(char *arg, int *error)
{
	unsigned long long	i;

	if (!arg)
		return (final_exit_code);
	i = 0;
	while (ft_isspace(arg[i]))
		i++;
	if (arg[i] == '\0')
		(*error) = 1;
	i += (arg[i] == '-' || arg[i] == '+');
	if (!ft_isdigit(arg[i]))
		(*error) = 1;
	while (arg[i])
	{
		if (!ft_isdigit(arg[i]) && !ft_isspace(arg[i]))
			(*error) = 1;
		i++;
	}
	i = ft_atoi_error(arg, error);
	return (i % 256);
}

/* is_quiet_mode:
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

/* exit_builtin:
*	Executes the exit builtin.
*	If alone, prints exit and exits the shell with the provided exit code, or 0.
*	If piped, exits the child process with the provided exit code and does not exit
*	minishell.
*	In case of failure due to invalid arguments, does not exit the shell
*	and returns an error exit code (1 or 2) instead.
*/
int	ft_exit(t_data *data, char **args)
{
	int		exit_code;
	int		error;

	error = 0;
	if (!silent_exit_check(data) && data->interactive)
		ft_printf(2, "exit\n");
	if (!args || !args[1])
		exit_code = final_exit_code;
	else
	{
		exit_code = get_exit_code(args[1], &error);
		if (error)
			exit_code = errmsg("exit", args[1], ARGERR04, 2);
		else if (args[2])
			return (errmsg("exit", NULL, ARGERR03, 1));
	}
	exit_full(data, exit_code);
	return (2);
}
