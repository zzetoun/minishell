/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzetoun <zzetoun@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 15:11:16 by zzetoun           #+#    #+#             */
/*   Updated: 2025/04/24 18:21:11 by zzetoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H
# include "../../include/minishell.h"

void    serealyze_tokens(int current, char *arg, t_token **token);
int     parse_tokens(int argc, char **argv, t_token **tonkens);
void    cmd_args_split(t_command *cmd, char *input);

#endif