/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_var.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzetoun <zzetoun@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 17:02:34 by zzetoun           #+#    #+#             */
/*   Updated: 2025/06/04 01:06:53 by zzetoun          ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../include/minishell.h"

static bool	erase_var(t_token **t_node, char *str, int index)
{
	int		idx;
	int		jdx;
	int		len;
	char	*new_str;

	idx = 0;
	jdx = 0;
	len = ft_strlen(str) - var_length(str + index);
	new_str = (char *)ft_calloc(len + 1, sizeof(char));
	if (!new_str)
		return (true);
	while (str[idx])
	{
		if (str[idx] == '$' && idx == index)
		{
			idx += var_length(str + index) + 1;
			if (str[idx] == '\0')
				break ;
		}
		new_str[jdx++] = str[idx++];
	}
	new_str[jdx] = '\0';
	ft_free_ptr((*t_node)->str);
	(*t_node)->str = new_str;
	return (false);
}

/* Changed return type from int to char * to adapt the function
*  to work for heredoc variable expansion. Heredoc has no tokens
*  so t_node becomes optional.
*  Heredoc variant replace_str_heredoc calls this function with
*  t_node == NULL!
*/
static char	*del_and_replace(t_token **t_node, char *str, char *var_val, int i)
{
	char	*newstr;
	int		len;

	len = (ft_strlen(str) - var_length(str + i) + ft_strlen(var_val));
	newstr = get_new_token_string(str, var_val, len, i);
	if (t_node && *t_node)
	{
		ft_free_ptr((*t_node)->str);
		(*t_node)->str = newstr;
	}
	return (newstr);
}

bool	replace_var(t_token **t_node, char *var_value, int index)
{
	if (!var_value)
	{
		if (erase_var(t_node, (*t_node)->str, index))
		{
			ft_free_ptr(var_value);
			return (true);
		}
	}
	else
	{
		if (!del_and_replace(t_node, (*t_node)->str, var_value, index))
		{
			ft_free_ptr(var_value);
			return (true);
		}
	}
	ft_free_ptr(var_value);
	return (false);
}

/* replace_str_heredoc:
*	Heredoc variant of replace_var, replaces an environment variable
*	by its value. Ex. $USER -> username.
*	Returns the replaced string.
*/
char	*replace_str_heredoc(char *str, char *var_value, int index)
{
	char	*new_str;

	if (!var_value)
		return (str);
	new_str = del_and_replace(NULL, str, var_value, index);
	if (!new_str)
		return (str);
	ft_free_ptr(str);
	return (new_str);
}
