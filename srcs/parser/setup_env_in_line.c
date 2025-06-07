/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_env_in_line.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzetoun <zzetoun@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 01:23:12 by igorsergeev       #+#    #+#             */
/*   Updated: 2025/06/07 19:03:08 by zzetoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	ft_free_dptr((void **)&sub);
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
	ft_free_dptr((void **)&var);
	if (!tmp) return -1;
	*dst = tmp;
	return (ssize_t)(j - 1);
}

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

//char *setup_env_in_line(const char *line, t_data *d)
//{
//	char    *out;
//	size_t  i;
//	bool    in_dq;
//
//	out = ft_strdup("");
//	if (!out)
//		return (NULL);
//	i = 0;
//	in_dq = false;
//	while (line[i])
//	{
//		if (line[i] == '"')
//		{
//			in_dq = !in_dq;
//			if (!add_literal(&out, '"'))
//				return (ft_free_dptr(out), NULL);
//		}
//		else if (line[i] == '\'' && !in_dq)
//		{
//			ssize_t r = handle_single_quotes(line, i, &out);
//			if (r < 0)
//				return (ft_free_dptr(out), NULL);
//			i = (size_t)r;
//		}
//		else if (line[i] == '$' && line[i + 1] == '?')
//		{
//			if (!add_exit_status_literal(&out))
//				return (ft_free_dptr(out), NULL);
//			++i;
//		}
//		else if (line[i] == '$' && line[i + 1] && line[i + 1] != '"' && line[i + 1] != '\'')
//		{
//			ssize_t r_var = handle_env(line, i, &out, d);
//			if (r_var < 0)
//				return (ft_free_dptr(out), NULL);
//			i = (size_t)r_var;
//		}
//		else
//		{
//			if (!add_literal(&out, line[i]))
//				return (ft_free_dptr(out), NULL);
//		}
//		++i;
//	}
//	return (out);
//}

#define ERR_INDEX SIZE_MAX

/* -------------------------------------------------------------------------- */
/*  Helper - add literal '"' and toggle double-quote state                    */
/* -------------------------------------------------------------------------- */
static size_t	handle_double_quote(bool *in_dq, char **out, size_t i)
{
	*in_dq = !*in_dq;
	if (!add_literal(out, '"'))
		return (ERR_INDEX);
	return (i + 1);
}

/* -------------------------------------------------------------------------- */
/*  Helper - copy content inside single quotes unchanged                      */
/* -------------------------------------------------------------------------- */
static size_t	handle_single_quotes_block(const char *l, size_t i, char **out)
{
	ssize_t r = handle_single_quotes(l, i, out);
	if (r < 0)
		return (ERR_INDEX);
	return ((size_t)r);
}

/* -------------------------------------------------------------------------- */
/*  Helper - expand $? exit status                                            */
/* -------------------------------------------------------------------------- */
static size_t	handle_exit_status(char **out, size_t i)
{
	if (!add_exit_status_literal(out))
		return (ERR_INDEX);
	return (i + 2);
}

/* -------------------------------------------------------------------------- */
/*  Helper - expand $VAR environment variables                                */
/* -------------------------------------------------------------------------- */
static size_t	handle_env_var(const char *l, size_t i, char **out, t_data *d)
{
	ssize_t r = handle_env(l, i, out, d);
	if (r < 0)
		return (ERR_INDEX);
	return ((size_t)r);
}

/* -------------------------------------------------------------------------- */
/*  Helper - add regular character                                            */
/* -------------------------------------------------------------------------- */
static size_t	handle_regular_char(const char *l, size_t i, char **out)
{
	if (!add_literal(out, l[i]))
		return (ERR_INDEX);
	return (i + 1);
}

/* -------------------------------------------------------------------------- */
/*  Central dispatcher for each token                                         */
/* -------------------------------------------------------------------------- */
static size_t	process_token(const char *l, size_t i, bool *in_dq,
							   char **out, t_data *d)
{
	if (l[i] == '"')
		return (handle_double_quote(in_dq, out, i));
	else if (l[i] == '\'' && !*in_dq)
		return (handle_single_quotes_block(l, i, out));
	else if (l[i] == '$' && l[i + 1] == '?')
		return (handle_exit_status(out, i));
	else if (l[i] == '$' && l[i + 1] && l[i + 1] != '"' && l[i + 1] != '\'')
		return (handle_env_var(l, i, out, d));
	else
		return (handle_regular_char(l, i, out));
}

/* -------------------------------------------------------------------------- */
/*  Public API: expand env-vars & quotes for a single input line               */
/* -------------------------------------------------------------------------- */
char    *setup_env_in_line(const char *line, t_data *d)
{
	char    *out;
	size_t  i;
	bool    in_dq;

	if (!line)
		return (NULL);
	out = ft_strdup("");
	if (!out)
		return (NULL);
	i = 0;
	in_dq = false;
	while (line[i])
	{
		i = process_token(line, i, &in_dq, &out, d);
		if (i == ERR_INDEX)
		{
			ft_free_dptr((void **)&out);
			return (NULL);
		}
	}
	return (out);
}
