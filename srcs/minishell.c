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

//int main (int ac, char **av, char **envp)
//{
//    (void) ac;
//    (void) av;
//    t_data      data;
//    t_env_info  env;
//    t_command cmd;
//
//    data.cmd = &cmd;
//    data.env = &env;
//	welcome_msg();
//    setup_mini(&data, &env, envp);
//    while (1)
//	{
//		data.user_input = readline(PROMPT);
//        //cmd_args_split(&cmd, data.user_input);
//        execute_cmd(&data, &cmd, &env);
//	}
//    return (0);
//}

static void print_data(t_data *data)
{
    t_token *token;

    token = data->token;
    while(token->next)
    {
        printf("value: %s\n", token->str);
        token = token->next;
    }
    printf("value: %s\n", token->str);
}

int main(void)
{
    t_data *data;

    welcome_msg();
    data = malloc(sizeof(t_data));
    if (!data)
        return (1);
    while (1)
    {
        data->user_input = readline(PROMPT);
        if (!data->user_input)
            break;
        if (!validate_input(data->user_input)) {
            data->user_input = check_if_additional(data->user_input);
            data->user_input = setup_env_in_line(data->user_input);
            data->token = setup_tokens((const char **)minishell_split(data->user_input));
            print_data(data);
        }
    }
    return (0);
}
