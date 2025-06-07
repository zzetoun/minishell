/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzetoun <zzetoun@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 19:06:36 by zzetoun           #+#    #+#             */
/*   Updated: 2025/06/07 19:06:57 by zzetoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENS_H
#define TOKENS_H

bool    tokenize_input(t_data *data, const char *input);
t_command	*add_new_cmd(bool value);
bool		add_back_cmd(t_command **list, t_command *new_node);
t_command	*last_cmd(t_command *cmd);
enum e_token_types  get_current_token_type(const char *current);

#endif
