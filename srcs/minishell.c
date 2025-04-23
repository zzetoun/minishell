/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzetoun <zzetoun@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 17:02:14 by zzetoun           #+#    #+#             */
/*   Updated: 2025/04/21 20:22:51 by zzetoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void welcome_msg(void)
{
	printf("\n\t###############################\n");
	printf("\t#                             #\n");
	printf("\t#  Minishell by Zorz & Igor   #\n");
	printf("\t#                             #\n");
	printf("\t###############################\n\n");
}

int main (int ac, char **av, char **envp)
{
    (void) ac;
    (void) av;
    t_data      data;
    t_env_info  env;
    t_command cmd;
	
	welcome_msg();
    setup_mini(&data, &env, envp);
    cmd.command = ft_strdup("pwd");
    while (1)
	{
		data.user_input = readline(PROMPT);    
        if (str_compare((data.user_input), PWD))
            execute_cmd(&data, &cmd);
	}
    return (0);
}
