/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzetoun <zzetoun@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 02:58:14 by igorsergeev       #+#    #+#             */
/*   Updated: 2025/06/08 16:06:41 by zzetoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
//TODO change realloc to allowed function
static char	**append_tok(char **arr, size_t *n, const char *s, size_t len)
{
	char	**tmp;
	char	*tok;

	tmp = realloc(arr, sizeof(*arr) * (*n + 2));
	if (!tmp)
	{
		perror("realloc");
		exit(1);
	}
	arr = tmp;
	tok = ft_substr(s, 0, len);
	arr[*n] = tok;
	arr[*n + 1] = NULL;
	(*n)++;
	return (arr);
}

//char	**minishell_split(char *input)
//{
//	char		**argv;
//	size_t		argc;
//	char		*p;
//	char		q;
//	char		*start;
//
//	argv = NULL;
//	argc = 0;
//	p = input;
//	while (*p)
//	{
//		while (*p && ft_isspace((unsigned char)*p))
//			p++;
//		if (!*p)
//			break ;
//		if ((p[0] == '<' && p[1] == '<') || (p[0] == '>' && p[1] == '>'))
//		{
//			argv = append_tok(argv, &argc, p, 2);
//			p += 2;
//			continue ;
//		}
//		if (*p == '<' || *p == '>' || *p == '|')
//		{
//			argv = append_tok(argv, &argc, p, 1);
//			p++;
//			continue ;
//		}
//		if (*p == '\'' || *p == '"')
//		{
//			q = *p++;
//			start = p;
//			while (*p && *p != q)
//				p++;
//			argv = append_tok(argv, &argc, start, p - start);
//			if (*p == q)
//				p++;
//			continue ;
//		}
//		start = p;
//		while (*p && !ft_isspace((unsigned char)*p) && *p
//			!= '<' && *p != '>' && *p != '|')
//			p++;
//		argv = append_tok(argv, &argc, start, p - start);
//	}
//	return (argv);
//}

static void skip_spaces(char **p)
{
	while (**p && ft_isspace((unsigned char)**p))
		++(*p);
}

/* True if the two‑char operator starts at *p (<< or >>) */
static bool is_dbl_op(const char *p)
{
	return ((p[0] == '<' && p[1] == '<') || (p[0] == '>' && p[1] == '>'));
}

/* Push substring [s, s+len) as a new token; realloc array via append_tok. */
static bool push_token(char ***argv, size_t *argc, const char *s, size_t len)
{
	*argv = append_tok(*argv, argc, s, len);
	return (*argv != NULL);
}

/* Parse double‑char operator (<< or >>). */
static bool parse_dbl_op(char ***argv, size_t *argc, char **p)
{
	if (!is_dbl_op(*p))
		return (false);
	if (!push_token(argv, argc, *p, 2))
		return (true);
	*p += 2;
	return (true);
}

/* Parse single‑char operator (<, >, |). */
static bool parse_sgl_op(char ***argv, size_t *argc, char **p)
{
	if (**p != '<' && **p != '>' && **p != '|')
		return (false);
	if (!push_token(argv, argc, *p, 1))
		return (true);
	++(*p);
	return (true);
}

/* Parse quoted string (single or double quotes). */
static bool parse_quoted(char ***argv, size_t *argc, char **p)
{
	char q;
	char *start;

	if (**p != '\'' && **p != '"')
		return (false);
	q = *(*p)++;
	start = *p;
	while (**p && **p != q)
		++(*p);
	if (!push_token(argv, argc, start, *p - start))
		return (true);
	if (**p == q)
		++(*p);
	return (true);
}

/* Parse unquoted word until space or operator. */
static bool parse_word(char ***argv, size_t *argc, char **p)
{
	char *start;

	start = *p;
	while (**p && !ft_isspace((unsigned char)**p)
		   && **p != '<' && **p != '>' && **p != '|')
		++(*p);
	return push_token(argv, argc, start, *p - start);
}

/* ─────────────────────── public tokenizer ─────────────────────────── */

char **minishell_split(char *input)
{
	char    **argv;
	size_t  argc;
	char    *p;

	argv = NULL;
	argc = 0;
	p = input;
	while (*p)
	{
		skip_spaces(&p);
		if (!*p)
			break ;
		if (parse_dbl_op(&argv, &argc, &p))
			continue ;
		if (parse_sgl_op(&argv, &argc, &p))
			continue ;
		if (parse_quoted(&argv, &argc, &p))
			continue ;
		if (!parse_word(&argv, &argc, &p))
			return (NULL);
	}
	return (argv);
}
