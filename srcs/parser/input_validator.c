//
// Created by IqMent on 11.05.2025.
//

#include <stddef.h>
#include <stdio.h>
#include "parser.h"

int validate_input(char *line)
{
    if (has_unclosed_quotes(line)) {
        printf("Error: unclosed quotes\n");
        return (1);
    }
    return (0);
}