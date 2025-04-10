/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imickhai <imickhai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 17:02:14 by zzetoun           #+#    #+#             */
/*   Updated: 2025/04/10 16:37:39 by imickhai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void setup_minishell(t_token *token)
{
	token->str = NULL;
	token->full_str = NULL;
}

int	main(int ac, char **av, char **envp)
{
	t_token	token;
	int		id;

	(void) ac;
	(void) av;
	(void) envp;
	setup_minishell(&token);
	// while (1)
	// {
	// 	id = -1;
	// 	token.str = readline("minishell> ");
	// 	token.full_str = ft_split(token.str, ' ');
	// 	while(token.full_str[++i])
	// 		printf("string: %s\n", token.full_str[i]);
	// 	ft_free_array(token.full_str);
	// }
	int n;
	id = fork();
	if (id == 0)
	 	n = 1;
	else
		n = 6;
	int i = n;
	if (id != 0)
		 wait(NULL);
	if (id != 0)
	{
		printf("I will print one time before excuting ls\n");
		execvp("/bin/ls", (char *[]){"/bin/ls", NULL});
		printf("you'll not see me\n");
	}
	while (i < n + 5)
	{
		printf("%d ", i);
		i++;
	}
	if (id == 0)
		printf("\n");
	return (0);
}
