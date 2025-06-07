/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exc.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzetoun <zzetoun@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 19:04:53 by zzetoun           #+#    #+#             */
/*   Updated: 2025/06/07 20:17:36 by zzetoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXC_H
# define EXC_H

int		cmd_is_dir(char *cmd);
int		execute(t_data *data);
int		str_compare(char const *s1, char const *s2);
int		check_cmd_not_found(t_data *data, t_command *cmd);
int		execute_bcmd(t_data *data, t_command *cmd);
int		execute_command(t_data *data, t_command *cmd);

char	*get_cmd_path(t_data *data, char *name);

#endif
