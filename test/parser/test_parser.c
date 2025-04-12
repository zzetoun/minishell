#include "../../srcs/parser/parser.h"
#include "../../include/minishell.h"
#include <stdio.h>

int main(int argc, char **argv)
{
    t_token **tokens;
    int     success;

    tokens = (t_token *)malloc(sizeof(t_token *));
    success = parse_tokens(argc, argv, tokens);
    
    return (0);
}