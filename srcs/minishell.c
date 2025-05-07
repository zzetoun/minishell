/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzetoun <zzetoun@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 18:18:14 by zzetoun           #+#    #+#             */
/*   Updated: 2025/05/07 18:18:14 by zzetoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	welcome_msg(void)
{
	ft_printf(1, "\n\t###############################\n");
	ft_printf(1, "\t#                               #\n");
	ft_printf(1, "\t#    Minishell by Zorz & Igor   #\n");
	ft_printf(1, "\t#							    #\n");
	ft_printf(1, "\t###############################\n\n");
}

int	main (int ac, char **av, char **envp)
{
	(void) ac;
	(void) av;
	t_data		data;
	t_env_info  env;
	t_command	cmd;

	data.cmd = &cmd;
	data.env = &env;
	welcome_msg();
	setup_mini(&data, envp);
	while (1)
	{
		data.user_input = readline(PROMPT);
		add_history(data.user_input);
		cmd_args_split(&cmd, data.user_input);
		execute_cmd(&data, &cmd, &env);
	}
	return (0);
}
