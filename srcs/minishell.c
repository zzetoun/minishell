/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzetoun <zzetoun@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 17:02:14 by zzetoun           #+#    #+#             */
/*   Updated: 2025/04/19 20:34:02 by zzetoun          ###   ########.fr       */
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
    (void) envp;
    char **new_env;
    t_data data;
	
    int i = -1;
    int len = 0;
	welcome_msg();
    while(envp[len])
        len++;
	ft_printf(1, "envp len:%d\n", len);
    new_env = ft_calloc(len + 1, sizeof(char *));
    if (!new_env)
        return (0);
	ft_printf(1, "**new_env is malloced\n");
    while(envp[++i])
    {
        new_env[i] = ft_calloc(ft_strlen(envp[i]), sizeof(char));
        if (!new_env[i])
            return(0);
        new_env[i] = ft_strdup(envp[i]);
		ft_printf(1, "envp[%d]: %s\n", i, envp[i]);
		ft_printf(1, "new_env[%d]: %s\n",i , new_env[i]);
    }
	ft_free_array(new_env);
	ft_printf(1, "**new_env is free\n");
    ft_printf(1, "getnvp of HOME: %s\n", getenv("HOME"));
    i = -1;
    while(envp[++i])
    {
        if (ft_strncmp(envp[i], "HOME", 4) == 0)
        {
            ft_printf(1, "old envp[%d]: %s\n", i, envp[i]);
            envp[i] = ft_strdup("HOME=/");
            ft_printf(1, "getnvp of new HOME: %s\n", getenv("HOME"));
        }
    }
    setup_mini(&data, envp);
    while (1)
	{
		data.user_input = readline(PROMPT);
        if (str_compare(str_tolower(data.user_input), PWD))
		    ft_printf(1, "working directort: \"%s\" \n", data.working_dir);
	}
    return (0);
}
