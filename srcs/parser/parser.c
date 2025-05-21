/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzetoun <zzetoun@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 15:26:03 by zzetoun           #+#    #+#             */
/*   Updated: 2025/05/21 15:26:07 by zzetoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <readline/readline.h>
#include <readline/history.h>

static char **append_tok(char **arr, size_t *n, const char *s, size_t len) {
    char **tmp = realloc(arr, sizeof(*arr)*(*n+2));
    if (!tmp) { perror("realloc"); exit(1); }
    arr = tmp;
    char *tok = strndup(s, len);
    arr[*n]   = tok;
    arr[*n+1] = NULL;
    (*n)++;
    return (arr);
}

char **minishell_split(const char *input)
{
    char **argv = NULL;
    size_t argc = 0;
    const char *p = input;

    while (*p) {
        while (*p && isspace((unsigned char)*p)) p++;
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
        if (*p=='\''||*p=='"') {
            char q = *p++;
            const char *start = p;
            while (*p && *p!=q) p++;
            argv = append_tok(argv, &argc, start, p-start);
            if (*p==q) p++;
            continue;
        }
        const char *start = p;
        while (*p && !isspace((unsigned char)*p)
               && *p!='<' && *p!='>' && *p!='|') p++;
        argv = append_tok(argv, &argc, start, p-start);
    }
    return (argv);
}
