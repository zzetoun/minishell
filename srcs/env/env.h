/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzetoun <zzetoun@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 18:23:32 by zzetoun           #+#    #+#             */
/*   Updated: 2025/04/27 12:30:24 by zzetoun          ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#ifndef ENV_H
# define ENV_H

size_t  ft_env_len(char **envp);

int     ft_env_setup(t_env_info *env, char **envp);
int     set_env(t_env_info *env, char *key, char *value);
int     ft_add_new_env(t_env_info *env, char *key, char *value);
int     ft_env_setup_null(t_env_info *env, size_t idx);

char    *get_env(t_env_info *env, char *key);

char     **ft_env_to_str(t_env_info *env);

#endif