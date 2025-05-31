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

//void	add_back_cmd(t_command **list, t_command *new_node)
//{
//    t_command	*start;
//
//    start = *list;
//    if (start == NULL)
//    {
//        *list = new_node;
//        return ;
//    }
//    if (list && *list && new_node)
//    {
//        while (start->next != NULL)
//            start = start->next;
//        start->next = new_node;
//        new_node->prev = start;
//    }
//}

//t_command	*add_new_cmd(bool value)
//{
//    t_command	*new_node;
//
//    new_node = (t_command *)ft_calloc(1, sizeof(t_command));
//    if (!new_node)
//    {
//        errmsg("malloc", NULL, MALLERR, EXIT_FAILURE);
//        return (NULL);
//    }
//    ft_memset(new_node, 0, sizeof(t_command));
//    new_node->pipe_output = value;
//    return (new_node);
//}

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
            cmd->pipe_output = 1;
            add_back_cmd(&data->cmd, add_new_cmd(false));
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
            cmd->io_fds->outfile = ft_strdup(split[++i]);
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

//static void add_back_cmd_token_type(t_command **cmd, t_command *new_node, enum e_token_types token_type) //TODO fix the tokenezation proccess bc my partner cannot works without tokenezation
//{
//    if (!cmd || !new_node) {
//        return; // Handle null pointers gracefully
//    }
//
//    new_node->token_type = token_type; // Set the token type for the new node
//
//    if (*cmd == NULL) {
//        *cmd = new_node; // If the list is empty, set the new node as the head
//    } else {
//        t_command *start = *cmd;
//        while (start->next != NULL) {
//            start = start->next; // Traverse to the end of the list
//        }
//        start->next = new_node; // Append the new node at the end
//        new_node->prev = start; // Set the previous pointer for the new node
//    }
//}

//static enum e_token_types   get_current_token_type(char *str)
//{
//    if (*str == '|')
//        return (PIPE);
//    else if (*str == '>' && str[1] == '>')
//        return (APPEND);
//    else if (*str == '<' && str[1] == '<')
//        return (HEREDOC);
//    else if (*str == '<')
//        return (INPUT);
//    else if (*str == '>')
//        return (TRUNC);
//    else if (*str == ' ')
//        return (SPACES);
//    else
//        return (WORD);
//}
//
//static char **append_arg(char **args, char *arg) {
//    size_t count;
//
//    count = 0;
//    if (args)
//    {
//        while (args[count])
//            count++;
//    }
//    char **new_args = malloc((count + 2) * sizeof(char *));
//    if (!new_args) {
//        perror("malloc");
//        exit(EXIT_FAILURE);
//    }
//    for (size_t i = 0; i < count; i++)
//        new_args[i] = args[i];
//    new_args[count] = strdup(arg);
//    if (!new_args[count]) {
//        perror("strdup");
//        exit(EXIT_FAILURE);
//    }
//    new_args[count + 1] = NULL;
//    if (args) {
//        free(args);
//    }
//    return (new_args);
//}

//bool cmd_args_split(t_data *data, char *input) {
//    size_t i = 0;
//    t_command *current_cmd = NULL;
//
//    if (!input || !*input)
//        return false;
//    add_history(input);
//    input = setup_env_in_line(input, data); // Process environment variables
//    while (input[i] != '\0') {
//        enum e_token_types token_type = get_current_token_type(&input[i]);
//
//        if (token_type == PIPE) {
//            t_command *new_cmd = add_new_cmd(true);
//            add_back_cmd_token_type(&data->cmd, new_cmd, PIPE);
//            current_cmd = last_command(data->cmd);
//            setup_io(current_cmd);
//            i++;
//        } else if (token_type == INPUT || token_type == TRUNC || token_type == APPEND || token_type == HEREDOC) {
//            if (!current_cmd) {
//                t_command *new_cmd = add_new_cmd(false);
//                add_back_cmd_token_type(&data->cmd, new_cmd, token_type);
//                current_cmd = last_command(data->cmd);
//                setup_io(current_cmd);
//            }
//            if (token_type == INPUT && input[i + 1]) {
//                current_cmd->io_fds->infile = ft_strdup(&input[i]);
//            } else if ((token_type == TRUNC || token_type == APPEND) && input[i + 1]) {
//                current_cmd->io_fds->outfile = ft_strdup(&input[++i]);
//            } else if (token_type == HEREDOC && input[i + 1]) {
//                current_cmd->io_fds->heredoc_delimiter = ft_strdup(&input[++i]);
//                current_cmd->io_fds->heredoc_quotes = has_quotes_1(current_cmd->io_fds->heredoc_delimiter);
//            }
//            i++;
//        } else if (token_type == WORD) {
//            if (!current_cmd) {
//                t_command *new_cmd = add_new_cmd(false);
//                add_back_cmd_token_type(&data->cmd, new_cmd, WORD);
//                current_cmd = last_command(data->cmd);
//                setup_io(current_cmd);
//            }
//            if (!current_cmd->command) {
//                current_cmd->command = ft_strdup(&input[i]);
//                current_cmd->args = append_arg(current_cmd->args, &input[i]);
//            } else {
//                current_cmd->args = append_arg(current_cmd->args, &input[i]);
//            }
//            while (input[i] != ' ' && input[i] != '\0' && input[i] != '|' && input[i] != '<' && input[i] != '>') {
//                i++;
//            }
//        } else {
//            i++;
//        }
//    }
//    return true;
//}
