/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expander.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzetoun <zzetoun@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 21:38:12 by zzetoun           #+#    #+#             */
/*   Updated: 2025/06/04 01:12:41 by zzetoun          ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../include/minishell.h"

/*
*  After splitting the user's input into tokens, we have to expand 
*  the variables. After the expansion is done, quote characters are
*  removed from the original word unless they are between quotes.
*/
static void	update_status(t_token **t_node, char c)
{
	if (c == '\'' && (*t_node)->status == DEFAULT)
		(*t_node)->status = SQUOTE;
	else if (c == '\"' && (*t_node)->status == DEFAULT)
		(*t_node)->status = DQUOTE;
	else if (c == '\'' && (*t_node)->status == SQUOTE)
		(*t_node)->status = DEFAULT;
	else if (c == '\"' && (*t_node)->status == DQUOTE)
		(*t_node)->status = DEFAULT;
}

static bool	is_next_char_a_sep(char c)
{
	if (c == '$' || c == ' ' || c == '=' || c == '\0')
		return (true);
	return (false);
}

static bool	var_between_quotes(char *str, int idx)
{
	if (idx > 0 && str[idx - 1] == '\"' && str[idx + 1] == '\"')
		return (true);
	return (false);
}

void	var_expander(t_data *data, t_token **token_lst)
{
	t_token	*token;
	int		idx;

	token = *token_lst;
	while (token)
	{
		if (token->type == VAR)
		{
			idx = 0;
			while (token->str[idx])
			{
				update_status(&token, token->str[idx]);
				if (token->str[idx] == '$'
					&& is_next_char_a_sep(token->str[idx + 1]) == false
					&& var_between_quotes(token->str, idx) == false
					&& (token->status == DEFAULT || token->status == DQUOTE))
					replace_var(&token,
						recover_val(token, token->str + idx, data), idx);
				else
					idx++;
			}
		}
		token = token->next;
	}
}

/* var_expander_heredoc:
*	Heredoc variant of var_expander. Replaces a string containing an
*	environment variable, like $USER with its corresponding value.
*	Returns the replaced string. May return NULL on error.
*/
char	*var_expander_heredoc(t_data *data, char *str)
{
	int		i;
	char	*new;
	char	*val;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$' && !is_next_char_a_sep(str[i + 1])
			&& !var_between_quotes(str, i))
		{
			val = recover_val(NULL, str + i, data);
			new = replace_str_heredoc(str, val, i);
			if (!new)
				return (str);
			str = new;
			if (val)
				i += ft_strlen(val);
			else
				i++;
			ft_free_ptr(val);
		}
		else
			i++;
	}
	return (str);
}

