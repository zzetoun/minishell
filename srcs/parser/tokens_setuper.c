//
// Created by IqMent on 17.05.2025.
//

#include "parser.h"
#include <string.h>

enum e_token_types get_token_type(const char *current)
{
    if (strcmp(current, "|") == 0)
        return (PIPE);
    if (strcmp(current, "<") == 0)
        return (REDIR_IN);
    if (strcmp(current, ">") == 0)
        return (REDIR_OUT);
    if (strcmp(current, "<<") == 0)
        return (HEREDOC);
    if (strcmp(current, ">>") == 0)
        return (APPEND);
    return (WORD);
}

t_token *setup_tokens(const char **user_input)
{
    size_t  i;
    t_token *root;
    t_token *current;
    t_token *prev;

    i = 0;
    root = malloc(sizeof(t_token));
    if (!root)
        return (NULL);
    root->prev = NULL;
    root->type = get_token_type(user_input[i]);
    root->str = ft_strdup(user_input[i]);
    if (!root)
        return (free(root), NULL);
    root->next = malloc(sizeof(t_token));
    if (!root->next)
        return (free(root->str),free(root), NULL);
    current = root->next;
    while (user_input[i])
    {
        current->prev = root;
        current->type = get_token_type(user_input[i]);
        current->str = ft_strdup(user_input[i]);
        if (!current->str)
            return (free(current), free(root->str), free(root), NULL);
        i++;
        if (user_input[i])
        {
            current->next = malloc(sizeof(t_token));
            if (!current->next)
                return (free(current->str), free(current), free(root->str), free(root), NULL);
            prev = current;
            current = current->next;
            current->prev = prev;
        }
    }
    return (current->next = NULL, root);
}