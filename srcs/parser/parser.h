/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imickhai <imickhai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 15:11:16 by zzetoun           #+#    #+#             */
/*   Updated: 2025/04/12 11:51:56 by imickhai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H
# include "../../include/minishell.h"

void    serealyze_tokens(int current, char *arg, t_token **token);
int     parse_tokens(int argc, char **argv, t_token **tonkens);

#endif