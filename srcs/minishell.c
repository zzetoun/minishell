/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzetoun <zzetoun@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 17:02:14 by zzetoun           #+#    #+#             */
/*   Updated: 2025/04/17 21:37:16 by zzetoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"


int	main(int ac, char **av, char **envp)
{
	t_data data;
	t_command cmd;
	(void) ac;

	setup_mini(&data, envp);
	cmd.command = ft_strdup(av[1]);
	execute_cmd(&data, &cmd);
	// while (1)
	// {
	// 	setup_mini(&data, envp);
	// 	data.user_input = readline(PROMPT);
	// 	if (cmd_compare(data.user_input, "pwd"))
	// 	ft_printf(1, "working directort: \"%s\" \n", data.working_dir);
	// }
	return (0);
}
