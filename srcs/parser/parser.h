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
bool                 has_quotes(const char *str);
bool                has_unclosed_quotes(const char *line);
char				*ft_replace_substr(const char *str, const char *target, const char *replacement);
void 				setup_last_exit_code(t_command *cmd, int last_exit_code);
void				clear_cmd(t_command **lst, void (*del)(void *));
void 				setup_truncate(t_io_fds *io);
void				setup_input(t_io_fds *io);
void			 	close_exists_red_fds(t_io_fds *fds);
void			 	setup_append(t_io_fds *io);

enum e_token_types  get_current_token_type(const char *str);
bool                cmd_args_split(t_data *data, char *input);
void                add_back_cmd_token_type(t_command **cmd, t_command *new_node, enum e_token_types token_type);

#endif
