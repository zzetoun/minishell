//
// Created by IqMent on 17.05.2025.
//

#include "tokens.h"

enum e_token_types  get_current_token_type(const char *current)
{
    if (*current == '|')
        return (PIPE);
    else if (*current == '<' && current[1] == '<')
        return (HEREDOC);
    else if (*current == '>' && current[1] == '>')
        return (APPEND);
    else if (*current == '>')
        return (TRUNC);
    else if (*current == '<')
        return (INPUT);
    else if (*current == ' ')
        return (SPACES);
    else if (*current == '$')
        return (VAR);
    else if (*current == '\0')
        return (END);
    return (WORD);
}

int has_quotes(const char *str)
{
    if (!str)
        return 0;
    while (*str)
    {
        if (*str == '\'' || *str == '"')
            return (1);
        str++;
    }
    return (0);
}

char **append_arg(char **args, const char *arg) {
    size_t count = 0;

    // Count existing arguments
    if (args) {
        while (args[count]) {
            count++;
        }
    }

    // Allocate memory for the new array (existing + new + NULL terminator)
    char **new_args = malloc((count + 2) * sizeof(char *));
    if (!new_args) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    // Copy existing arguments to the new array
    for (size_t i = 0; i < count; i++) {
        new_args[i] = args[i];
    }

    // Add the new argument
    new_args[count] = strdup(arg);
    if (!new_args[count]) {
        perror("strdup");
        exit(EXIT_FAILURE);
    }

    // Null-terminate the array
    new_args[count + 1] = NULL;

    // Free the old array if it exists
    if (args) {
        free(args);
    }

    return new_args;
}

bool tokenize_input(t_data *data, const char *input) {
    size_t i = 0;
    t_command *current_cmd = NULL;

    if (!input || !*input || !data)
        return false;

    while (input[i] != '\0') {
        enum e_token_types token_type = get_current_token_type(&input[i]);

        if (token_type == PIPE) {
            add_back_cmd(&data->cmd, add_new_cmd(true));
            current_cmd = last_cmd(data->cmd);
            setup_io(current_cmd);
            i++;
        } else if (token_type == INPUT || token_type == TRUNC || token_type == APPEND || token_type == HEREDOC) {
            // Handle redirections
            if (!current_cmd) {
                add_back_cmd(&data->cmd, add_new_cmd(false));
                current_cmd = last_cmd(data->cmd);
                setup_io(current_cmd);
            }
            if (token_type == INPUT && input[i + 1]) {
                current_cmd->io_fds->infile = ft_strdup(&input[++i]);
            } else if ((token_type == TRUNC || token_type == APPEND) && input[i + 1]) {
                current_cmd->io_fds->outfile = ft_strdup(&input[++i]);
            } else if (token_type == HEREDOC && input[i + 1]) {
                current_cmd->io_fds->heredoc_delimiter = ft_strdup(&input[++i]);
                current_cmd->io_fds->heredoc_quotes = has_quotes(current_cmd->io_fds->heredoc_delimiter);
            }
            i++;
        } else if (token_type == WORD) {
            if (!current_cmd) {
                add_back_cmd(&data->cmd, add_new_cmd(false));
                current_cmd = last_cmd(data->cmd);
                setup_io(current_cmd);
            }
            if (!current_cmd->command) {
                current_cmd->command = ft_strdup(&input[i]);
                current_cmd->args = append_arg(current_cmd->args, &input[i]);
            } else {
                current_cmd->args = append_arg(current_cmd->args, &input[i]);
            }
            while (input[i] != ' ' && input[i] != '\0' && input[i] != '|' && input[i] != '<' && input[i] != '>') {
                i++;
            }
        } else {
            i++;
        }
    }
    return (true);
}
