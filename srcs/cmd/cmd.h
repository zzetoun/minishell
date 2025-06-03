/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzetoun <zzetoun@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 22:56:28 by zzetoun           #+#    #+#             */
/*   Updated: 2025/05/06 22:56:28 by zzetoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMD_H
# define CMD_H

int		ft_pwd(t_data *data);
int		export_args_check(char *arg, char *cmd);
int		ft_exit(t_data *data, char **args);
int		ft_echo(char **args);
int		ft_env(t_env_info *env, char **args, size_t idx);
int		ft_unset(t_env_info *env, char **args);
int		ft_export(t_env_info *env, char **args);
int		ft_cd(t_data *data, char **arg, t_env_info *env);

void	free_env(t_env_info *env);

#endif
