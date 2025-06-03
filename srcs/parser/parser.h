/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzetoun <zzetoun@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 17:41:34 by zzetoun           #+#    #+#             */
/*   Updated: 2025/06/03 16:23:38 by zzetoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

t_command	*add_new_cmd(void);
t_command	*get_last_cmd(t_command *cmd);

void		remove_empty_var_args(t_token **tokens);
void		create_cmd(t_data *data, t_token *token);
void		clear_cmd(t_command **lst, void (*del)(void *));
void		parse_pipe(t_command **cmd, t_token **token_lst);
void		parse_word(t_command **cmd, t_token **token_lst);
void		add_back_cmd(t_command **list, t_command *new_node);
void		fill_args(t_token **t_node, t_command *last_cmd);
void		parse_trunc(t_command **last_cmd, t_token **token_lst);
void		parse_input(t_command **last_cmd, t_token **token_lst);
void		parse_append(t_command **last_cmd, t_token **token_list);
void		parse_heredoc(t_data *data, t_command **l_cmd, t_token **token_ls);

bool		cmd_args_split(t_data *data, char *input);
bool		remove_old_file_ref(t_io_fds *io, bool infile);
bool		add_args(t_token **t_node, t_command *last_cmd);
bool		fill_heredoc(t_data *data, t_io_fds *io, int fd);
bool		create_args(t_token **t_node, t_command *last_cmd);
bool		add_args_echo(t_token **t_node, t_command *last_cmd);
bool		create_args_echo(t_token **t_node, t_command *last_cmd);

char		*join_vars(t_token **t_node);
char		*get_relative_path(char *file_to_open);
char		**copy_in_ntab(int len, char **ntab, t_command *lcmd, t_token *tk);

int			count_args(t_token *token);
int			count_args_echo(t_token *token);

#endif
