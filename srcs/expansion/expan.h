/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expan.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzetoun <zzetoun@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 16:33:15 by zzetoun           #+#    #+#             */
/*   Updated: 2025/06/02 21:44:54 by zzetoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPAN_H
# define EXPAN_H

int		var_length(char *str);
int		count_len(char *str, int count, int idx);

bool	is_var_compliant(char c);
bool	quotes_in_string(char *str);
bool	replace_var(t_token **t_node, char *var_value, int index);

void	handle_quotes(t_data *data);
void	remove_quotes(t_token **t_node);
void	var_expander(t_data *data, t_token **token_lst);
void	copy_var_value(char *new_str, char *var_value, int *jdx);

char	*identify_var(char *str);
char	*var_expander_heredoc(t_data *data, char *str);
char	*recover_val(t_token *token, char *str, t_data *data);
char	*replace_str_heredoc(char *str, char *var_value, int index);
char	*get_new_token_string(char *oldstr, char *var_val, int len, int index);

#endif
