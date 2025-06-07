/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_validator.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzetoun <zzetoun@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 01:48:58 by igorsergeev       #+#    #+#             */
/*   Updated: 2025/06/07 19:04:40 by zzetoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void init_variables_with_zero(size_t *v1, size_t *v2, size_t *v3, size_t *v4)
{
	if (v1)
		*v1 = 0;
	if (v2)
		*v2 = 0;
	if (v3)
		*v3 = 0;
	if (v4)
		*v4 = 0;
}

static bool quotes_error(const char *line)
{
	size_t squotes_count;
	size_t dquotes_count;
	size_t position;
	size_t last_squote_position;
	size_t last_dquote_position;

	init_variables_with_zero(&squotes_count, &dquotes_count, &position, &last_squote_position);
	last_dquote_position = 0;
	while (line[position])
	{
		if (line[position] == '\'')
		{
			squotes_count++;
			if (squotes_count % 2 == 1)
				last_squote_position = position;
		}
		else if (line[position] == '"')
		{
			dquotes_count++;
			if (dquotes_count % 2 == 1)
				last_dquote_position = position;
		}
		position++;
	}
	if (squotes_count % 2 == 1 || dquotes_count % 2 == 1) {
		printf("%s\n", line);
		for (size_t i = 0; i < position; i++) {
			if ((squotes_count % 2 == 1 && i == last_squote_position) ||
				(dquotes_count % 2 == 1 && i == last_dquote_position))
				putchar('^');
			else
				putchar(' ');
		}
		printf(" - Unclosed quotes\n");
		return (false);
	}
	return (true);
}

bool	validate_input(const char *input)
{
	if (!input || !*input)
		return (true);
	return (quotes_error(input));
}
