
#include "parser.h"

//TOKENS: << >> < > | & && $ $? ; ' " \ ( )

// static char **get_tokens_list(void)
// {
//     char    **tokens;

//     tokens = (char **)malloc(sizeof(char *) * 16);
//     // <<
//     tokens[0] = (char *)malloc(sizeof(char) * 3);
//     tokens[0] = "<<\0";
//     // >>
//     tokens[1] = (char *)malloc(sizeof(char) * 3);
//     tokens[1] = ">>\0";
//     // <
//     tokens[2] = (char *)malloc(sizeof(char) * 2);
//     tokens[0] = "<\0";

// }

void    serealyze_tokens(int current, char *arg, t_token **token)
{
    if (current < 0)
        return;
    if (!arg)
        return;
    if (!token)
        return;
    return;
}

int parse_tokens(int argc, char **argv, t_token **tokens)
{
    if (argc < 0)
        return (0);
    if (!argv)
        return (0);
    if (!tokens)
        return (0);
    return (1);
}