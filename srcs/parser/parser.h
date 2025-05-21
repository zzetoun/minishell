//
// Created by IqMent on 16.05.2025.
//

#ifndef MINISHELL_MASTER_PARSER_H
#define MINISHELL_MASTER_PARSER_H

#include "../../include/struct_mini.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include "../libft/libft.h"

t_token *setup_tokens(const char **user_input);
int     validate_input(const char *user_input);
char    *ft_strndup(char *s, size_t n);
enum    e_token_types get_token_type(const char *current);
char **minishell_split(const char *input);
char *setup_env_in_line(char *line);
char *ft_strndup(char *str, size_t n);
char	*check_if_additional(char *line);

#endif //MINISHELL_MASTER_PARSER_H
