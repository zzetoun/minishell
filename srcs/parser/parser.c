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

t_command *last_command(t_command *cmd)
{
    while (cmd && cmd->next)
        cmd = cmd->next;
    return (cmd);
}

char **append_arg_1(char **args, const char *arg)
{
    int i = 0;
    char **new_args;

    if (!args)
    {
        new_args = malloc(sizeof(char *) * 2);
        new_args[0] = ft_strdup(arg);
        new_args[1] = NULL;
        return new_args;
    }
    while (args[i])
        i++;
    new_args = malloc(sizeof(char *) * (i + 2));
    for (int j = 0; j < i; j++)
        new_args[j] = args[j];
    new_args[i] = ft_strdup(arg);
    new_args[i + 1] = NULL;
    free(args);
    return new_args;
}

void free_split(char **split)
{
    if (!split)
        return;
    for (int i = 0; split[i]; i++)
        free(split[i]);
    free(split);
}


int has_quotes_1(const char *str)
{
    if (!str)
        return 0;
    while (*str)
    {
        if (*str == '\'' || *str == '"')
            return 1;
        str++;
    }
    return 0;
}

static void	parse_pipe(t_command **cmd, t_token **token_lst) // <--- t_token **token_lst is optional
{
    t_command	*last_cmd;
    last_cmd = last_command(*cmd);// <---- you go to the last command and send it's output to 1 since the command your in is the input
    last_cmd->pipe_output = 1;
    add_back_cmd(&last_cmd, add_new_cmd(0));
    if (token_lst && *token_lst)
        *token_lst = (*token_lst)->next; // <-- go to the next token, unless you go to the next one outside
}

bool	cmd_args_split(t_data *data, char *input)
{
    char	**split;
    int		i;
    t_command *cmd;

    if (input)
        add_history(input);
    else
        return (false);
    input = setup_env_in_line(input, data);
    split = minishell_split(input);
    if (!split) {
        return (false);
    }

    i = 0;
    while (split[i])
    {
        if (!cmd)
        {
            add_back_cmd(&data->cmd, add_new_cmd(false));
            cmd = last_command(data->cmd);
            setup_io(cmd);
        }
        if (strcmp(split[i], "|") == 0)
        {
            parse_pipe(&data->cmd, NULL);
            cmd = last_command(data->cmd);
            setup_io(cmd);
            i++;
            continue;
        }
        cmd = last_command(data->cmd);
        if (strcmp(split[i], "<") == 0 && split[i+1])
            cmd->io_fds->infile = ft_strdup(split[++i]);
        else if (strcmp(split[i], ">") == 0 && split[i+1])
            cmd->io_fds->outfile = ft_strdup(split[++i]);
        else if (strcmp(split[i], ">>") == 0 && split[i+1])
            cmd->io_fds->append_file = ft_strdup(split[++i]);
        else if (strcmp(split[i], "<<") == 0 && split[i+1])
        {
            cmd->io_fds->heredoc_delimiter = ft_strdup(split[++i]);
            cmd->io_fds->heredoc_quotes = has_quotes(cmd->io_fds->heredoc_delimiter);
        }
        else
        {
            if (!cmd->command)
            {
                cmd->token_type = WORD;
                cmd->command = ft_strdup(split[i]);
                cmd->args = append_arg_1(cmd->args, split[i]);
            }
            else {
                cmd->args = append_arg_1(cmd->args, split[i]);
            }
        }
        i++;
    }
    free_split(split);
    return (true);
}
