/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recover_value.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzetoun <zzetoun@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 16:47:37 by zzetoun           #+#    #+#             */
/*   Updated: 2025/06/03 21:33:14 by zzetoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*recover_val(t_token *token, char *str, t_data *data)
{
	char	*value;
	char	*var;

	var = identify_var(str);
	if (var && get_env(data->env, var))
	{
		if (token != NULL)
			token->var_exists = true;
		value = ft_strdup(get_env(data->env, var));
	}
	else if (var && var[0] == '?')
		value = ft_itoa(g_final_exit_code);
	else
		value = NULL;
	ft_free_ptr(var);
	return (value);
}
