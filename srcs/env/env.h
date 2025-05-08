/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzetoun <zzetoun@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 23:02:42 by zzetoun           #+#    #+#             */
/*   Updated: 2025/05/06 23:02:42 by zzetoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

size_t	ft_darray_len(char **str);

int		ft_env_setup_null(t_env_info *env);
int		env_key(t_env_info *env, char *key);
int		set_env(t_env_info *env, char *key, char *value);
int		ft_key_cmp(const char *str, const char *key);
int		ft_env_setup(t_env_info *env, char **envp, size_t idx);
int		add_new_env(t_env_info *env, char *key, char *value);

char	*get_env(t_env_info *env, char *key);

char	**env_tostr(t_env_info *env);

void	ft_set_key_value(t_envp *new_env, char *envp, char *key, char *value);

#endif
