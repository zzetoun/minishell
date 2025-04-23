/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzetoun <zzetoun@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 15:11:49 by zzetoun           #+#    #+#             */
/*   Updated: 2025/04/18 16:52:18 by zzetoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMD_H
#define CMD_H

int ft_pwd(t_data *data);
int ft_cd(t_data *data, char **arg);
int ft_env(t_data *data, char **arg);
int ft_exit(t_data *data, char **arg);
int ft_echo(t_data *data, char **arg);
int ft_unset(t_data *data, char **arg);
int ft_export(t_data *data, char **arg);
int str_compare(char const *s1, char const *s2);
int	execute_cmd(t_data *data, t_command *cmd);

#endif