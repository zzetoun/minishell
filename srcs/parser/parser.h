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

/* ##### commands parsing & cleanup & setup ##### */
t_command	*add_new_cmd(bool value);
t_command	*get_last_cmd(t_command *cmd);
void		add_back_cmd(t_command **list, t_command *new_node);
void		list_del_cmd(t_command *list, void (*del)(void *));
void		list_clear_cmd(t_command **list, void (*del)(void *));

bool		cmd_args_split(t_data *data, char *input);

#endif
