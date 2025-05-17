//
// Created by IqMent on 09.05.2025.
//

#include "parser.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <readline/readline.h>
#include <readline/history.h>

//static char *copy_until_quote(char *line, size_t *i, char quote)
//{
//    size_t start = *i;
//    (*i)++;
//    while (line[*i] && line[*i] != quote)
//        (*i)++;
//    if (line[*i] == quote)
//        (*i)++;
//    return ft_strndup(line + start, *i - start);
//}
//
//static char *copy_until_space(char *line, size_t *i)
//{
//    size_t start = *i;
//    while (line[*i] && line[*i] != ' ' && line[*i] != '\'' && line[*i] != '\"')
//        (*i)++;
//    return ft_strndup(line + start, *i - start);
//}

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

//t_data  *setup_parsered_data(t_data **data, const char *user_input)
//{
//    char    **tokens;
//    size_t  i;
//    t_data *temp;
//
//    temp = *data;
//    i = 0;
//    if (validate_input(user_input) != 0)
//        return (fprintf(stderr, "Error: invalid input\n"), NULL);
//    else
//    {
//        tokens = minishell_split(user_input);
//        if (!tokens)
//            return (fprintf(stderr, "Error with split by tokens\n"), NULL);
//        while (tokens[i])
//        {
//            temp->token = get_token_type(tokens[i]);
//        }
//    }
//}