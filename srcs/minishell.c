/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzetoun <zzetoun@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 17:02:14 by zzetoun           #+#    #+#             */
/*   Updated: 2025/04/21 16:46:24 by zzetoun          ###   ########.fr       */
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
    int i = -1;
	
	welcome_msg();
	ft_printf(1, "envp len:%d\n", ft_env_len(envp));
    setup_mini(&data, &env, envp);
    while(data.env[++i])
        ft_printf(1, "data.env:{%s}\n", data.env[i]);
    while (1)
	{
		data.user_input = readline(PROMPT);
        if (str_compare(str_tolower(data.user_input), PWD)) // str_tolower is going to be used with commands promts only
		    ft_printf(1, "working directort: \"%s\" \n", data.working_dir);
	}
    return (0);
}
