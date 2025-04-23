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

int     ft_free_env(t_env_info *env);
int     ft_env_setup(t_env_info *env, char **envp);

char     **ft_env_to_str(t_env_info *env);

char    *get_env_value(t_env_info *env, char *term);
int     set_env_value(t_env_info *env, char *term, char *value);

void    linked_list_print(t_env_info  *env, char **_envp);

#endif