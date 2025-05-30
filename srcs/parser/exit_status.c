//
// Created by iqment on 5/29/25.
//

#include "parser.h"

void    setup_last_exit_status(t_command *current)
{
    size_t  i;

    i = 0;
    while (current->args && current->args[i])
    {
        if (ft_strncmp(current->args[i], "$?", 2) == 0)
        {
            free(current->args[i]);
            current->args[i] = ft_itoa(g_final_exit_code);
            if (!current->args[i])
            {
                perror("Error allocating memory for exit status");
                exit(EXIT_FAILURE);
            }
        }
        i++;
    }
    return ;
}
