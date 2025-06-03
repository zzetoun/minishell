/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_args_echo.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzetoun <zzetoun@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 19:56:47 by zzetoun           #+#    #+#             */
/*   Updated: 2025/06/03 15:35:29 by zzetoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
*  This function deals with the specific case when the command is "echo"
*    - It allocates the array of arguments thanks to the count_args_echo
*		function
*    - It loops through the tokens list while the nodes are of type
*        VAR or WORD: 
*         * If "bool join = true" in the token structure is true : we join all
*           the tokens of type VAR that have the setting "join = true"
*         * if "join = false" we just fill the last_cmd_>args[i] 
*            with the current token.
*/
bool	create_args_echo(t_token **t_node, t_command *last_cmd)
{
	t_token	*token;
	int		idx;

	remove_empty_var_args(t_node);
	token = *t_node;
	last_cmd->args = ft_calloc((count_args_echo(token) + 2), sizeof(char *));
	if (!last_cmd->args)
		return (errmsg("malloc", NULL, MALLERR, false));
	last_cmd->args[0] = ft_strdup(last_cmd->command);
	idx = 1;
	while (token->type == WORD || token->type == VAR)
	{
		if (token->join == true)
			last_cmd->args[idx] = join_vars(&token);
		else
			last_cmd->args[idx] = ft_strdup(token->str);
		idx++;
		token = token->next;
	}
	last_cmd->args[idx] = NULL;
	*t_node = token;
	return (true);
}

bool	add_args_echo(t_token **t_node, t_command *last_cmd)
{
	int		len;
	char	**new_tab;
	t_token	*token;

	remove_empty_var_args(t_node);
	token = *t_node;
	len = 0;
	while (last_cmd->args[len])
		len++;
	new_tab = ft_calloc((count_args_echo(token) + len + 1), sizeof(char *));
	if (!new_tab)
		return (errmsg("malloc", NULL, MALLERR, false));
	new_tab = copy_in_ntab(len, new_tab, last_cmd, token);
	ft_free_array(last_cmd->args);
	last_cmd->args = new_tab;
	while (token->type == WORD || token->type == VAR)
		token = token->next;
	*t_node = token;
	return (true);
}
