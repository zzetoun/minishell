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

//size_t  handle_single_quotes(char *line, size_t i, char **result)
//{
//    size_t	start;
//	char 	*sub_str;
//
//    start = ++i;
//    while (line[i] && line[i] != '\'')
//		i++;
//	sub_str = ft_substr(line, start, i - start);
//	if (!sub_str)
//		sub_str = ft_strdup("");
//    *result = ft_strjoin_free(*result,sub_str);
//	ft_free_ptr(sub_str);
//    return (i);
//}
//
//size_t  handle_env_variable(char *line, size_t i, char **result, t_data *data)
//{
//    size_t  j;
//	char    *env_var;
//	char    *env_val;
//
//    j = i + 1;
//    while (line[j] && (ft_isalnum(line[j]) || line[j] == '_'))
//        j++;
//    env_var = ft_strndup(line + i + 1, j - i - 1);
//    env_val = get_env(data->env, env_var);
//    if (!env_val)
//        env_val = ft_strdup("");
//    if (env_val)
//        *result = ft_strjoin_free(*result, env_val);
//    ft_free_ptr(env_var);
//    return (j - 1);
//}
//
//void    append_char(char **result, const char c)
//{
//	char tmp[2];
//
//	tmp[0] = c;
//	tmp[1] = '\0';
//	*result = ft_strjoin_free(*result, tmp);
//}
//
//char    *setup_env_in_line(char *line, t_data *data)
//{
//    char	*result;
//	size_t	i;
//	int		in_double_quotes;
//
//	result = ft_strdup("");
//	i = (size_t)-1;
//    in_double_quotes = 0;
//    while (line[++i])
//    {
//        if (line[i] == '"')
//        {
//            in_double_quotes = !in_double_quotes;
//            append_char(&result, '"');
//        }
//        else if (line[i] == '\'' && !in_double_quotes)
//            i = handle_single_quotes(line, i, &result);
//        else if (line[i] == '$' && line[i + 1] == '?')
//        {
//            append_char(&result, '$');
//            append_char(&result, '?');
//            i++;
//        }
//        else if (line[i] == '$' && (line[i + 1] != '"' && line[i + 1] != '\''))
//            i = handle_env_variable(line, i, &result,data);
//        else
//            append_char(&result, line[i]);
//    }
//    return result;
//}

//static char *join_and_free(char *a, const char *b)
//{
//	char *res = ft_strjoin(a, b);
//	ft_free_ptr(a);
//	return res;
//}

static bool append_char(char **dst, char c)
{
	char buf[2] = { c, 0 };
	char *tmp = ft_strjoin_free(*dst, buf);
	if (!tmp)
		return false;
	*dst = tmp;
	return true;
}

/* -------- single quotes -------- */
static ssize_t handle_single_quotes(const char *s, size_t i, char **dst)
{
	size_t start = ++i;
	while (s[i] && s[i] != '\'')
		i++;
	char *sub = ft_substr(s, start, i - start);
	if (!sub && errno == ENOMEM)
		return -1;
	char *tmp = ft_strjoin_free(*dst, sub ? sub : "");
	ft_free_ptr(sub);
	if (!tmp)
		return -1;
	*dst = tmp;
	return (ssize_t)i; /* caller ++ */
}

/* -------- env variable -------- */
static bool is_env_char(char c)
{
	return ft_isalnum((unsigned char)c) || c == '_';
}

static ssize_t handle_env(const char *s, size_t i, char **dst, t_data *d)
{
	size_t j = i + 1;
	while (s[j] && is_env_char(s[j]))
		j++;
	char *var = ft_strndup(s + i + 1, j - i - 1);
	if (!var) return -1;
	char *val = get_env(d->env, var);
	if (!val) val = "";
	char *tmp = ft_strjoin_free(*dst, val);
	ft_free_ptr(var);
	if (!tmp) return -1;
	*dst = tmp;
	return (ssize_t)(j - 1); /* caller ++ */
}

/* -------- public API -------- */
char *setup_env_in_line(const char *line, t_data *d)
{
	char *out = ft_strdup("");
	if (!out)
		return NULL;

	bool dq = false;
	for (size_t i = 0; line[i]; ++i)
	{
		if (line[i] == '"')
		{
			dq = !dq;
			if (!append_char(&out, '"'))
				return (ft_free_ptr(out), NULL);
		}
		else if (line[i] == '\'' && !dq)
		{
			ssize_t r = handle_single_quotes(line, i, &out);
			if (r < 0)
				return (ft_free_ptr(out), NULL);
			i = (size_t)r; /* цикл ++ ещё добавит 1 */
		}
		else if (line[i] == '$' && line[i + 1] == '?')
		{
			if (!append_char(&out, '$') || !append_char(&out, '?'))
				return (ft_free_ptr(out), NULL);
			++i; /* пропустить '?' */
		}
		else if (line[i] == '$' && line[i + 1] && line[i + 1] != '"' && line[i + 1] != '\'')
		{
			ssize_t r = handle_env(line, i, &out, d);
			if (r < 0)
				return (ft_free_ptr(out), NULL);
			i = (size_t)r;
		}
		else
		{
			if (!append_char(&out, line[i]))
				return (ft_free_ptr(out), NULL);
		}
	}
	return out;
}
