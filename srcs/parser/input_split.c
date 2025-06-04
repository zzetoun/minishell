//
// Created by iqment on 6/3/25.
//

#include "parser.h"

static char **append_tok(char **arr, size_t *n, const char *s, size_t len) {
	char **tmp = realloc(arr, sizeof(*arr)*(*n+2));//TODO change it to allowed function
	if (!tmp)
	{
		perror("realloc");
		exit(1);
	}
	arr = tmp;
	char *tok = ft_strndup(s, len);
	arr[*n] = tok;
	arr[*n + 1] = NULL;
	(*n)++;
	return (arr);
}

char **minishell_split(char *input)
{
	char		**argv;
	size_t		argc;
	char		*p;
	char		q;
	char 		*start;

	argv = NULL;
	argc = 0;
	p = input;
	while (*p)
	{
		while (*p && isspace((unsigned char)*p))
			p++;
		if (!*p)
			break;
		if ((p[0]=='<' && p[1]=='<') || (p[0]=='>' && p[1]=='>')) {
			argv = append_tok(argv, &argc, p, 2);
			p += 2;
			continue;
		}
		if (*p=='<'||*p=='>'||*p=='|') {
			argv = append_tok(argv, &argc, p, 1);
			p++;
			continue;
		}
		if (*p=='\''||*p=='"')
		{
			q = *p++;
			start = p;
			while (*p && *p!=q)
				p++;
			argv = append_tok(argv, &argc, start, p-start);
			if (*p==q)
				p++;
			continue;
		}
		start = p;
		while (*p && !isspace((unsigned char)*p) && *p!='<' && *p!='>' && *p!='|')
			p++;
		argv = append_tok(argv, &argc, start, p-start);
	}
	return (argv);
}
