//
// Created by iqment on 5/31/25.
//

#include "../parser.h"

//int has_quotes(const char *str)
//{
//    if (!str || !*str)
//        return (-1);
//    while(*str)
//    {
//        if (*str == '\'' || *str == '"')
//            return (1);
//        str++;
//    }
//    return (0);
//}

//enum e_token_types  get_current_token_type(const char *str)
//{
//    if (*str == '|')
//        return (PIPE);
//    if (*str == '>' && str[1] == '>')
//        return (APPEND);
//    if (*str == '<' && str[1] == '<')
//        return (HEREDOC);
//    if (*str == '<')
//        return (INPUT);
//    if (*str == '>')
//        return (TRUNC);
//    if (*str == ' ')
//        return (SPACES);
//    if (*str == '\0')
//        return (END);
//    else
//        return (WORD);
//}

void add_back_cmd_token_type(t_command **cmd, t_command *new_node, enum e_token_types token_type) //TODO fix the tokenezation proccess bc my partner cannot works without tokenezation
{
    if (!cmd || !new_node)
        return;
    new_node->token_type = token_type;
    if (*cmd == NULL)
        *cmd = new_node;
    else
    {
        t_command *start = *cmd;
        while (start->next != NULL) {
            start = start->next;
        }
        start->next = new_node;
        new_node->prev = start;
    }
}
