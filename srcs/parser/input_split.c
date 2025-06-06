/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igorsergeevic <igorsergeevic@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 02:58:14 by igorsergeev       #+#    #+#             */
/*   Updated: 2025/06/07 01:06:39 by igorsergeev      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
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
	tok = ft_strndup(s, len);
	arr[*n] = tok;
	arr[*n + 1] = NULL;
	(*n)++;
	return (arr);
}

char	**minishell_split(char *input)
{
	char		**argv;
	size_t		argc;
	char		*p;
	char		q;
	char		*start;

	argv = NULL;
	argc = 0;
	p = input;
	while (*p)
	{
		while (*p && ft_isspace((unsigned char)*p))
			p++;
		if (!*p)
			break ;
		if ((p[0] == '<' && p[1] == '<') || (p[0] == '>' && p[1] == '>'))
		{
			argv = append_tok(argv, &argc, p, 2);
			p += 2;
			continue ;
		}
		if (*p == '<' || *p == '>' || *p == '|')
		{
			argv = append_tok(argv, &argc, p, 1);
			p++;
			continue ;
		}
		if (*p == '\'' || *p == '"')
		{
			q = *p++;
			start = p;
			while (*p && *p != q)
				p++;
			argv = append_tok(argv, &argc, start, p - start);
			if (*p == q)
				p++;
			continue ;
		}
		start = p;
		while (*p && !ft_isspace((unsigned char)*p) && *p
			!= '<' && *p != '>' && *p != '|')
			p++;
		argv = append_tok(argv, &argc, start, p - start);
	}
	return (argv);
}
