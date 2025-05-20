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

//static void welcome_msg(void)
//{
//	printf("\n\t###############################\n");
//	printf("\t#                             #\n");
//	printf("\t#  Minishell by Zorz & Igor   #\n");
//	printf("\t#                             #\n");
//	printf("\t###############################\n\n");
//}

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

//static void free_parsed_data(t_data **data)
//{
//    t_token *tmp;
//    t_token *current;
//
//    current = (*data)->token;
//    while (current)
//    {
//        tmp = current;
//        current = current->next;
//        free(tmp->str);
//        free(tmp);
//    }
//}

static void free_parsed_tokens(t_token *token)
{
    t_token *tmp;

    while(token)
    {
        tmp = token->next;
        free(token->str);
        free(token);
        token = tmp;
    }
}

//static void free_user_input(char **user_input)
//{
//    size_t  i;
//
//    i = 0;
//    while(user_input[i])
//    {
//        free(user_input[i]);
//    }
//    free(user_input);
//}

int main(void)
{
    t_data *data;
    char **splited_user_input = NULL;

    data = malloc(sizeof(t_data));
    if (!data)
        return (1);

    while (1)
    {
        data->user_input = readline(PROMPT);
        if (!data->user_input)
            break;

        if (!validate_input(data->user_input))
        {
            char *tmp = check_if_additional(data->user_input);
            if (tmp != data->user_input)
            {
                free(data->user_input);
                data->user_input = tmp;
            }

            tmp = setup_env_in_line(data->user_input);
            if (tmp != data->user_input)
            {
                free(data->user_input);
                data->user_input = tmp;
            }

            splited_user_input = minishell_split(data->user_input);
            data->token = setup_tokens((const char **)splited_user_input);

            print_data(data);

            free_parsed_tokens(data->token);

            if (splited_user_input)
            {
                for (size_t i = 0; splited_user_input[i]; i++)
                    free(splited_user_input[i]);
                free(splited_user_input);
                splited_user_input = NULL;
            }
        }

        free(data->user_input);
        data->user_input = NULL;
    }

    free(data);
    return (0);
}
