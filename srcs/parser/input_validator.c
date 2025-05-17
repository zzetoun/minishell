//
// Created by IqMent on 11.05.2025.
//

#include <stddef.h>
#include <stdio.h>

static int handle_unclosed_quotes(const char *line)
{
    char state = 0;  // 0 = вне кавычек, '\'' = в одинарных, '"' = в двойных
    size_t i = 0;

    while (line[i])
    {
        if (state == 0 && (line[i] == '"' || line[i] == '\''))
            state = line[i];
        else if (state == line[i])
            state = 0;
        i++;
    }
    return (state != 0);
}

int validate_input(char *line)
{
    if (handle_unclosed_quotes(line)) {
        printf("Error: unclosed quotes\n");
        return (1);
    }
    return (0);
}