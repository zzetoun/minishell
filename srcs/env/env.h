/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzetoun <zzetoun@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 18:23:32 by zzetoun           #+#    #+#             */
/*   Updated: 2025/04/29 20:38:19 by zzetoun          ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#ifndef ENV_H
# define ENV_H

size_t  ft_darray_len(char **str);

int     ft_env_setup_null(t_env_info *env);
int     set_env(t_env_info *env, char *key, char *value);
int     ft_key_cmp(const char *str, const char *key);
int     ft_env_setup(t_env_info *env, char **envp, size_t idx);
int     ft_add_new_env(t_env_info *env, char *key, char *value);

char    *get_env(t_env_info *env, char *key);

char    **ft_env_to_str(t_env_info *env);
char    **ft_env_to_export(t_env_info *env);

#endif