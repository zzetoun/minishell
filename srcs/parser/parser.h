//
// Created by IqMent on 16.05.2025.
//

#ifndef MINISHELL_MASTER_PARSER_H
#define MINISHELL_MASTER_PARSER_H

#include "../../include/minishell.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include "../utils/libft/libft.h"
#include "../tokens/tokens.h"


t_token *setup_tokens(const char **user_input);
int     validate_input(const char *user_input);
char    *ft_strndup(const char *s, size_t n);
enum    e_token_types get_token_type(const char *current);
char **minishell_split(const char *input);
char *setup_env_in_line(char *line, t_data *data);
//char *ft_strndup(char *str, size_t n);
char	*check_if_additional(char *line, t_data *data);
bool	cmd_args_split(t_data *data, char *input);
void append_char(char **result, const char c);
size_t handle_single_quotes(char *line, size_t i, char **result);
size_t handle_env_variable(char *line, size_t i, char **result, t_data *data);
//void    setup_exit_status(t_command *cmd);
//void replace_exit_status_in_args(t_command *cmd);
void    setup_last_exit_status(t_command *current);
char **append_arg(char **args, const char *arg);

#endif //MINISHELL_MASTER_PARSER_H
