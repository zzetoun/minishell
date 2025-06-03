/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expander_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzetoun <zzetoun@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 21:38:06 by zzetoun           #+#    #+#             */
/*   Updated: 2025/06/03 21:38:09 by zzetoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	copy_var_value(char *new_str, char *var_value, int *jdx)
{
	int	kdx;

	kdx = 0;
	while (var_value[kdx])
	{
		new_str[*jdx] = var_value[kdx];
		kdx++;
		(*jdx)++;
	}
}

char	*get_new_token_string(char *oldstr, char *var_val, int len, int index)
{
	int		idx;
	int		jdx;
	char	*new_str;

	idx = 0;
	jdx = 0;
	new_str = ft_calloc(len, sizeof(char));
	if (!new_str)
	{
		errmsg("malloc", NULL, MALLERR, EXIT_FAILURE);
		return (NULL);
	}
	while (oldstr[idx])
	{
		if (oldstr[idx] == '$' && idx == index)
		{
			copy_var_value(new_str, var_val, &jdx);
			idx += var_length(oldstr + index) + 1;
			if (oldstr[idx] == '\0')
				break ;
		}
		new_str[jdx++] = oldstr[idx++];
	}
	new_str[jdx] = '\0';
	return (new_str);
}
