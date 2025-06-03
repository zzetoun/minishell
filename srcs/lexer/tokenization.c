/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzetoun <zzetoun@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 15:39:08 by zzetoun           #+#    #+#             */
/*   Updated: 2025/06/03 14:04:09 by zzetoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
*	This function divides the given string (user input) into two
*   types of tokens : words or separators (pipes, heredoc , etc)
*	It checks each char of the string and defines if it is a separator or 
*   a word and then saves the token in a linked list.
*   Also checks if there is an unclosed quote error and defines which
*   separators will be evaluated following the single or double quoting rules:
*   
*   -Without quotes, bash tries to evaluate all special characters
*   -Single quotes (') prevent all evaluation
*   -Double quotes (") prevent most evaluation,
*		but notably not the evaluation of variables
*
*/

bool	tokenization(t_data *data, char *str)
{
	int	idx;
	int	end;
	int	start;
	int	status;

	idx = -1;
	start = 0;
	end = ft_strlen(str);
	status = DEFAULT;
	while (++idx <= end)
	{
		status = set_status(status, str, idx);
		if (status == DEFAULT)
			start = save_word_or_sep(&idx, str, start, data);
	}
	if (status != DEFAULT)
	{
		if (status == DQUOTE)
			errmsg(EOFERR, "quotes", "\"", EXIT_SUCCESS);
		else if (status == SQUOTE)
			errmsg(EOFERR, "quotes", "\'", EXIT_SUCCESS);
		errmsg("syntax error", NULL, "unexpected end of file", EXIT_FAILURE);
		return (false);
	}
	return (true);
}
