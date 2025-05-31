/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzetoun <zzetoun@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 17:41:34 by zzetoun           #+#    #+#             */
/*   Updated: 2025/05/30 16:02:43 by zzetoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

#include "../../include/struct_mini.h"
#include "../../include/minishell.h"
#include <stdbool.h>

/* ##### commands parsing & cleanup & setup ##### */
t_command	        *add_new_cmd(bool value);
t_command	*get_last_cmd(t_command *cmd);
void		        add_back_cmd(t_command **list, t_command *new_node);
void		list_del_cmd(t_command *list, void (*del)(void *));
void		list_clear_cmd(t_command **list, void (*del)(void *));
char                *setup_env_in_line(char *line, t_data *data);
char                *ft_strndup(const char *s, size_t n);
int                 has_quotes(const char *str);
enum e_token_types  get_current_token_type(const char *str);
bool                cmd_args_split(t_data *data, char *input);
void                add_back_cmd_token_type(t_command **cmd, t_command *new_node, enum e_token_types token_type);

#endif
