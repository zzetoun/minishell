/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_args_default.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzetoun <zzetoun@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 18:12:43 by zzetoun           #+#    #+#             */
/*   Updated: 2025/06/03 20:31:10 by zzetoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	count_args(t_token *token)
{
	int	idx;

	idx = 0;
	while (token && (token->type == WORD || token->type == VAR))
	{
		idx++;
		token = token->next;
	}
	return (idx);
}

/*
*  This function fills the array of arguments of the get_last_cmd
* 	by default mode:
*    - It allocates the array of arguments thanks to the count_args_echo
*	 function
*    - It loops through the tokens list while the nodes are of type
*        VAR or WORD, and fills get_last_cmd->args[i] with the current token
*/
bool	create_args(t_token **t_node, t_command *last_cmd)
{
	int		idx;
	t_token	*token;

	token = *t_node;
	last_cmd->args = ft_calloc((count_args(token) + 2), sizeof(char *));
	if (!last_cmd->args)
	{
		errmsg("malloc", NULL, MALLERR, EXIT_FAILURE);
		return (false);
	}
	token = *t_node;
	last_cmd->args[0] = ft_strdup(last_cmd->command);
	idx = 1;
	while (token->type == WORD || token->type == VAR)
	{
		last_cmd->args[idx++] = ft_strdup(token->str);
		token = token->next;
	}
	last_cmd->args[idx] = NULL;
	*t_node = token;
	return (true);
}

static char	**copy_to_ntab(
	int len, char **ntab, t_command *last_cmd, t_token **t_node)
{
	int		idx;
	t_token	*token;

	idx = -1;
	token = *t_node;
	while (++idx < len)
		ntab[idx] = last_cmd->args[idx];
	while (token->type == WORD || token->type == VAR)
	{
		ntab[idx++] = ft_strdup(token->str);
		token = token->next;
	}
	ntab[idx] = NULL;
	return (ntab);
}

bool	add_args(t_token **t_node, t_command *last_cmd)
{
	int		idx;
	int		len;
	char	**new_tab;
	t_token	*token;

	idx = 0;
	token = *t_node;
	while (token->type == WORD || token->type == VAR)
	{
		idx++;
		token = token->next;
	}
	len = 0;
	while (last_cmd->args[len])
		len++;
	new_tab = ft_calloc((idx + len + 1), sizeof(char *));
	if (!new_tab)
		return (errmsg("malloc", NULL, MALLERR, false));
	new_tab = copy_to_ntab(len, new_tab, last_cmd, t_node);
	ft_free_array(last_cmd->args);
	last_cmd->args = new_tab;
	*t_node = token;
	return (true);
}

/*
**  This function fills the arguments in the command structure (command->args)
**  It has two modes: 
**    - The "echo mode" if the command is the builtin "echo"
**    - The default mode for all the other cases
*/
void	fill_args(t_token **token_node, t_command *last_cmd)
{
	if (str_compare(last_cmd->command, "echo"))
	{
		if (!(last_cmd->args))
			create_args_echo(token_node, last_cmd);
		else
			add_args_echo(token_node, last_cmd);
	}
	else
	{
		if (last_cmd && !(last_cmd->args))
			create_args(token_node, last_cmd);
		else
			add_args(token_node, last_cmd);
	}
}
