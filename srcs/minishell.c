/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzetoun <zzetoun@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 17:02:14 by zzetoun           #+#    #+#             */
/*   Updated: 2025/04/27 18:17:07 by zzetoun          ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

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
