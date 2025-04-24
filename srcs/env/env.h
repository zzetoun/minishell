/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzetoun <zzetoun@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 18:23:32 by zzetoun           #+#    #+#             */
/*   Updated: 2025/04/21 19:47:23 by zzetoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

size_t  ft_env_len(char **envp);

int     ft_env_setup(t_env_info *env, char **envp);
int     set_env_value(t_env_info *env, char *term, char *value);
int     ft_add_new_env(t_env_info *env, t_envp *envp, char *value);

char    *get_env_value(t_env_info *env, char *term);

char     **ft_env_to_str(t_env_info *env);

#endif