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

static char *join_and_free(char *a, const char *b)
{
	char *res = ft_strjoin(a, b);
	ft_free_dptr((void *) &a);
	return res;
}

static bool append_char(char **dst, char c)
{
	char buf[2] = { c, 0 };
	char *tmp = join_and_free(*dst, buf);
	if (!tmp)
		return false;
	*dst = tmp;
	return true;
}

static ssize_t handle_single_quotes(const char *s, size_t i, char **dst)
{
	size_t start = ++i;
	while (s[i] && s[i] != '\'')
		i++;
	char *sub = ft_substr(s, start, i - start);
	if (!sub && errno == ENOMEM)
		return -1;
	char *tmp = join_and_free(*dst, sub ? sub : "");
	ft_free_ptr(sub);
	if (!tmp)
		return -1;
	*dst = tmp;
	return (ssize_t)i;
}

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
	char *tmp = join_and_free(*dst, val);
	ft_free_ptr(var);
	if (!tmp) return -1;
	*dst = tmp;
	return (ssize_t)(j - 1);
}

//char *setup_env_in_line(const char *line, t_data *d)
//{
//	char *out = ft_strdup("");
//	if (!out)
//		return NULL;
//
//	bool dq = false;
//	for (size_t i = 0; line[i]; ++i)
//	{
//		if (line[i] == '"')
//		{
//			dq = !dq;
//			if (!append_char(&out, '"'))
//				return (ft_free_ptr(out), NULL);
//		}
//		else if (line[i] == '\'' && !dq)
//		{
//			ssize_t r = handle_single_quotes(line, i, &out);
//			if (r < 0)
//				return (ft_free_ptr(out), NULL);
//			i = (size_t)r; /* цикл ++ ещё добавит 1 */
//		}
//		else if (line[i] == '$' && line[i + 1] == '?')
//		{
//			if (!append_char(&out, '$') || !append_char(&out, '?'))
//				return (ft_free_ptr(out), NULL);
//			++i;
//		}
//		else if (line[i] == '$' && line[i + 1] && line[i + 1] != '"' && line[i + 1] != '\'')
//		{
//			ssize_t r = handle_env(line, i, &out, d);
//			if (r < 0)
//				return (ft_free_ptr(out), NULL);
//			i = (size_t)r;
//		}
//		else
//		{
//			if (!append_char(&out, line[i]))
//				return (ft_free_ptr(out), NULL);
//		}
//	}
//	return out;
//}

static bool add_literal(char **dst, char c)
{
	return (append_char(dst, c));
}

/* handle \$? -> literally "$?" */
static bool add_exit_status_literal(char **dst)
{
	if (!add_literal(dst, '$'))
		return (false);
	return (add_literal(dst, '?'));
}

/* ─────────────────────── main expander ───────────────────── */

char *setup_env_in_line(const char *line, t_data *d)
{
	char    *out;
	size_t  i;
	bool    in_dq;

	out = ft_strdup("");
	if (!out)
		return (NULL);
	i = 0;
	in_dq = false;
	while (line[i])
	{
		if (line[i] == '"')
		{
			in_dq = !in_dq;
			if (!add_literal(&out, '"'))
				return (ft_free_ptr(out), NULL);
		}
		else if (line[i] == '\'' && !in_dq)
		{
			ssize_t r = handle_single_quotes(line, i, &out);
			if (r < 0)
				return (ft_free_ptr(out), NULL);
			i = (size_t)r;
		}
		else if (line[i] == '$' && line[i + 1] == '?')
		{
			if (!add_exit_status_literal(&out))
				return (ft_free_ptr(out), NULL);
			++i;
		}
		else if (line[i] == '$' && line[i + 1] && line[i + 1] != '"' && line[i + 1] != '\'')
		{
			ssize_t r_var = handle_env(line, i, &out, d);
			if (r_var < 0)
				return (ft_free_ptr(out), NULL);
			i = (size_t)r_var;
		}
		else
		{
			if (!add_literal(&out, line[i]))
				return (ft_free_ptr(out), NULL);
		}
		++i;
	}
	return (out);
}

