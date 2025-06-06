/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_env_in_line.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igorsergeevic <igorsergeevic@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 01:23:12 by igorsergeev       #+#    #+#             */
/*   Updated: 2025/06/07 01:26:53 by igorsergeev      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

size_t  handle_single_quotes(char *line, size_t i, char **result)
{
    size_t	start;
	char 	*sub_str;

    start = ++i;
    while (line[i] && line[i] != '\'')
		i++;
	sub_str = ft_substr(line, start, i - start);
	if (!sub_str)
		sub_str = ft_strdup("");
    *result = ft_strjoin_free(*result,sub_str);
	ft_free_ptr(sub_str);
    return (i);
}

size_t  handle_env_variable(char *line, size_t i, char **result, t_data *data)
{
    size_t  j;
	char    *env_var;
	char    *env_val;

    j = i + 1;
    while (line[j] && (ft_isalnum(line[j]) || line[j] == '_'))
        j++;
    env_var = ft_strndup(line + i + 1, j - i - 1);
    env_val = get_env(data->env, env_var);
    if (!env_val)
        env_val = ft_strdup("\n");
    if (env_val)
        *result = ft_strjoin_free(*result, env_val);
    ft_free_ptr(env_var);
    return (j - 1);
}

void    append_char(char **result, const char c)
{
	char tmp[2];

	tmp[0] = c;
	tmp[1] = '\0';
	*result = ft_strjoin_free(*result, tmp);
}

char    *setup_env_in_line(char *line, t_data *data)
{
    char	*result;
	size_t	i;
	int		in_double_quotes;

	result = ft_strdup("");
	i = (size_t)-1;
    in_double_quotes = 0;
    while (line[++i])
    {
        if (line[i] == '"')
        {
            in_double_quotes = !in_double_quotes;
            append_char(&result, '"');
        }
        else if (line[i] == '\'' && !in_double_quotes)
            i = handle_single_quotes(line, i, &result);
        else if (line[i] == '$' && line[i + 1] == '?')
        {
            append_char(&result, '$');
            append_char(&result, '?');
            i++;
        }
        else if (line[i] == '$' && (line[i + 1] != '"' && line[i + 1] != '\''))
            i = handle_env_variable(line, i, &result,data);
        else
            append_char(&result, line[i]);
    }
    return result;
}
