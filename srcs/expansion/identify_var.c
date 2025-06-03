/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   identify_var.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzetoun <zzetoun@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 16:31:14 by zzetoun           #+#    #+#             */
/*   Updated: 2025/06/03 21:34:28 by zzetoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

bool	is_var_compliant(char c)
{
	if (ft_isalnum(c) == 0 && c != '_')
		return (false);
	else
		return (true);
}

int	var_length(char *str)
{
	int		idx;
	int		count;

	count = 0;
	idx = 0;
	while (str[idx] != '$')
		idx++;
	if ((str[++idx] >= '0' && str[idx] <= '9') || str[idx] == '?')
		return (count + 1);
	while (str[idx])
	{
		if (!is_var_compliant(str[idx]))
			break ;
		count++;
		idx++;
	}
	return (count);
}

char	*identify_var(char *str)
{
	char	*var;
	int		start;
	int		idx;

	idx = -1;
	start = 0;
	while (str[++idx])
	{
		if (str[idx] == '$')
		{
			start = idx + 1;
			break ;
		}
	}
	var = ft_substr(str, start, var_length(str));
	ft_printf(1, "var = [%s]", var);
	if (!var)
		return (NULL);
	return (var);
}
