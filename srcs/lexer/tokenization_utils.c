/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzetoun <zzetoun@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 15:39:34 by zzetoun           #+#    #+#             */
/*   Updated: 2025/06/03 14:20:42 by zzetoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	save_separator(t_token **token_list, char *str, int index, int type)
{
	int		idx;
	char	*sep;

	idx = 0;
	if (type == APPEND || type == HEREDOC)
	{
		sep = ft_calloc(3, sizeof(char));
		if (!sep)
			return (1);
		while (idx < 2)
			sep[idx++] = str[index++];
		sep[idx] = '\0';
		add_back_token(token_list, add_new_token(sep, NULL, type, DEFAULT));
	}
	else
	{
		sep = ft_calloc(2, sizeof(char));
		if (!sep)
			return (1);
		while (idx < 1)
			sep[idx++] = str[index++];
		sep[idx] = '\0';
		add_back_token(token_list, add_new_token(sep, NULL, type, DEFAULT));
	}
	return (0);
}

static void	save_word(t_token **token_list, char *str, int index, int start)
{
	int		idx;
	char	*wr;

	idx = 0;
	wr = ft_calloc((index - start + 1), sizeof(char));
	if (!wr)
		return ;
	while (start < index)
	{
		wr[idx] = str[start];
		start++;
		idx++;
	}
	wr[idx] = '\0';
	add_back_token(token_list, add_new_token(wr, ft_strdup(wr), WORD, DEFAULT));
}

int	is_separator(char *str, int idx)
{
	if (((str[idx] > 8 && str[idx] < 14) || str[idx] == 32))
		return (SPACES);
	else if (str[idx] == '|')
		return (PIPE);
	else if (str[idx] == '<' && str[idx + 1] == '<')
		return (HEREDOC);
	else if (str[idx] == '>' && str[idx + 1] == '>')
		return (APPEND);
	else if (str[idx] == '<')
		return (INPUT);
	else if (str[idx] == '>')
		return (TRUNC);
	else if (str[idx] == '\0')
		return (END);
	else
		return (0);
}

int	set_status(int status, char *str, int idx)
{
	if (str[idx] == '\'' && status == DEFAULT)
		status = SQUOTE;
	else if (str[idx] == '\"' && status == DEFAULT)
		status = DQUOTE;
	else if (str[idx] == '\'' && status == SQUOTE)
		status = DEFAULT;
	else if (str[idx] == '\"' && status == DQUOTE)
		status = DEFAULT;
	return (status);
}

int	save_word_or_sep(int *idx, char *str, int start, t_data *data)
{
	int	type;

	type = is_separator(str, (*idx));
	if (type)
	{
		if ((*idx) != 0 && is_separator(str, (*idx) - 1) == 0)
			save_word(&data->token, str, (*idx), start);
		if (type == APPEND || type == HEREDOC || type == PIPE
			|| type == INPUT || type == TRUNC || type == END)
		{
			save_separator(&data->token, str, (*idx), type);
			if (type == APPEND || type == HEREDOC)
				(*idx)++;
		}
		start = (*idx) + 1;
	}
	return (start);
}
