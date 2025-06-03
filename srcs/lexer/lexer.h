/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzetoun <zzetoun@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 15:32:42 by zzetoun           #+#    #+#             */
/*   Updated: 2025/06/03 14:19:56 by zzetoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

t_token	*add_new_token(char *str, char *str_backup, int type, int status);
t_token	*insert_lst_between(t_token **head, t_token *to_del, t_token *insert);

bool	parse_user_input(t_data *data);
bool	check_if_var(t_token **token_lst);
bool	tokenization(t_data *data, char *str);
bool	check_consecutives(t_token **token_lst);

int		set_status(int status, char *str, int idx);
int		save_word_or_sep(int *idx, char *str, int start, t_data *data);
int		save_separator(t_token **token_lst, char *str, int index, int type);

void	clear_token(t_token **list, void (*del)(void *));
void	del_one_token(t_token *list, void (*del)(void *));
void	add_back_token(t_token **list, t_token *new_node);

#endif
