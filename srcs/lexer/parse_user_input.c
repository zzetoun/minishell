/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_user_input.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzetoun <zzetoun@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 15:40:27 by zzetoun           #+#    #+#             */
/*   Updated: 2025/06/03 14:01:55 by zzetoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static bool	input_is_space(char *input)
{
	int	idx;

	idx = -1;
	while (input[++idx])
		if (!ft_isspace(input[idx]))
			return (false);
	return (true);
}

/* parse_user_input:
*	Tokenizes and parses user input into a structure for execution.
*	Returns true if successful, false in case of error.
*/
bool	parse_user_input(t_data *data)
{
	if (!data->user_input)
		ft_exit(data, NULL);
	else if (str_compare(data->user_input, "\0"))
		return (false);
	else if (input_is_space(data->user_input))
		return (true);
	add_history(data->user_input);
	if (!tokenization(data, data->user_input))
		return (false);
	if (data->token->type == END)
		return (false);
	if (!check_if_var(&data->token))
		return (false);
	var_expander(data, &data->token);
	handle_quotes(data);
	create_cmd(data, data->token);
	return (true);
}
