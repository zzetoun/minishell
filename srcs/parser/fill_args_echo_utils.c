/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_args_echo_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzetoun <zzetoun@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 20:19:16 by zzetoun           #+#    #+#             */
/*   Updated: 2025/06/04 02:25:45 by zzetoun          ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../include/minishell.h"

/*
**  This function joins all the tokens of a quoted sentence
**  (ex " Hello $user") that was previously split.
**  To join them, the tokens have to be of type VAR and the join
**  setting must be set to true (the quotes are implied)
**  The function is only used when the command is "echo".
**  
**  ex: The strings -> "Hello" "  " "world"
**      become "Hello  world"
*/
char	*join_vars(t_token **t_node)
{
	char	*str;
	t_token	*token;

	token = *t_node;
	str = ft_strdup(token->str);
	while (token->type == VAR && token->next->type == VAR
		&& token->next->join == true)
	{
		str = ft_strjoin_free(str, token->next->str);
		token = token->next;
	}
	*t_node = token;
	return (str);
}

/*
**  This function counts the number of arguments in the list of tokens
**  To consider a token or multiple tokens as an argument they must be either
**  a WORD or a VAR and if they	temp = *t_node;
 are a VAR that has to be joined, we have
**  to loop through all the tokens that check these conditions 
**  (type == VAR and join == true) before counting them as one argument
*/
int	count_args_echo(t_token *token)
{
	int	idx;

	idx = 0;
	while (token && (token->type == WORD || token->type == VAR))
	{
		if (token->type == VAR && token->join == true)
		{
			while (token->type == VAR && token->join == true)
				token = token->next;
			idx++;
		}
		else
		{
			idx++;
			token = token->next;
		}
	}
	return (idx);
}

char	**copy_in_ntab(int len, char **ntab, t_command *lcmd, t_token *tk)
{
	int	idx;

	idx = -1;
	while (++idx < len)
		ntab[idx] = lcmd->args[idx];
	while (tk->type == WORD || tk->type == VAR)
	{
		if (tk->join == true)
			ntab[idx] = join_vars(&tk);
		else
			ntab[idx] = ft_strdup(tk->str);
		idx++;
		tk = tk->next;
	}
	ntab[idx] = NULL;
	return (ntab);
}

/* remove_empty_var_args:
**	If a variable does not exist in the environment, the token string
**	will contain "\0". In this case, echo should not print the variable
**	or any spaces before/after it. Therefore the token must be
**	removed before creating/adding echo args.
**	i.e., if variable X does not exist in environment,
**		'echo $X $X $X $USER' should print:
**		'username' (not '  username')
**	However, if the variable exists but its value is empty, the token
**	should not be removed.
*/
void	remove_empty_var_args(t_token **tokens)
{
	t_token	*token;

	token = *tokens;
	while (token->type == WORD || token->type == VAR)
	{
		if (token->type == VAR && token->str[0] == '\0'
			&& token->var_exists == false)
		{
			token = token->next;
			if (token == (*tokens)->next)
				(*tokens) = (*tokens)->next;
			del_one_token(token->prev, ft_free_ptr);
		}
		else
			token = token->next;
	}
}
