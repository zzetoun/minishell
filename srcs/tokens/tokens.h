//
// Created by iqment on 5/30/25.
//

#ifndef MINISHELL_TOKENS_H
#define MINISHELL_TOKENS_H

#include "../../include/struct_mini.h"
#include "../../include/minishell.h"
#include <stdbool.h>

bool    tokenize_input(t_data *data, const char *input);

// CMD_utils
t_command	*add_new_cmd(bool value);
void	add_back_cmd(t_command **list, t_command *new_node);
t_command	*last_cmd(t_command *cmd);
enum e_token_types  get_current_token_type(const char *current);

#endif //MINISHELL_TOKENS_H
