/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_setup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzetoun <zzetoun@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 15:27:26 by zzetoun           #+#    #+#             */
/*   Updated: 2025/05/08 15:27:26 by zzetoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_set_key_value(t_envp *new_env, char *envp, char *key, char *value)
{
	size_t	len;

	if (envp)
	{
		len = ft_strlen(envp) - ft_strlen(ft_strchr(envp, '='));
		new_env->value = ft_strdup(ft_strchr(envp, '=') + 1);
		new_env->key = ft_substr(envp, 0, len);
		new_env->str = ft_strjoin(new_env->key, "=");
		new_env->str = ft_strjoin_free(new_env->str, new_env->value);
	}
	else
	{
		new_env->key = ft_strdup(key);
		if (value != NULL)
		{
			new_env->str = ft_strjoin(key, "=");
			new_env->value = ft_strdup(value);
		}
		else
		{
			new_env->str = ft_strdup(key);
			new_env->value = NULL;
		}
		new_env->str = ft_strjoin_free(new_env->str, value);
	}
}

int	ft_env_setup(t_env_info *env, char **envp, size_t idx)
{
	t_envp	*new_env;
	t_envp	*last;

	env->head = NULL;
	if (!envp || !*envp)
		return (ft_env_setup_null(env));
	last = NULL;
	while (++idx < ft_darray_len(envp))
	{
		new_env = ft_calloc(1, sizeof(t_envp));
		if (!new_env)
			return (ft_free_env(env), 1);
		ft_set_key_value(new_env, envp[idx], NULL, NULL);
		new_env->idx = idx;
		new_env->next = NULL;
		if (last)
			last->next = new_env;
		else
			env->head = new_env;
		last = new_env;
	}
	env->size = idx;
	env->shlvl = ft_atoi(get_env(env, "SHLV"));
	return (0);
}

int	ft_env_setup_null(t_env_info *env)
{
	char	buff[PATH_MAX];

	env->size = 0;
	if (add_new_env(env, "OLDPWD", NULL))
		return (1);
	if (add_new_env(env, "PATH", PATHEN))
		return (1);
	if (add_new_env(env, "PWD", getcwd(buff, PATH_MAX)))
		return (1);
	if (add_new_env(env, "SHLVL", "1"))
		return (1);
	env->shlvl = ft_atoi(get_env(env, "SHLV"));
	if (add_new_env(env, "_", "/usr/bin/env"))
		return (1);
	return (0);
}

char	*get_env(t_env_info *env, char *key)
{
	t_envp	*envp;

	envp = env->head;
	while (envp)
	{
		if (ft_strncmp(envp->key, key, ft_strlen(key)) == 0)
			return (envp->value);
		envp = envp->next;
	}
	return (NULL);
}

int	set_env(t_env_info *env, char *key, char *value)
{
	t_envp	*envp;

	envp = env->head;
	while (envp && key)
	{
		if (str_compare(key, "_"))
			return (0);
		if (!ft_strncmp(envp->key, key, ft_strlen(key)))
		{
			ft_free_ptr(envp->value);
			envp->value = ft_strdup(value);
			ft_free_ptr(envp->str);
			envp->str = ft_strjoin(key, "=");
			envp->str = ft_strjoin_free(envp->str, value);
			return (0);
		}
		envp = envp->next;
	}
	return (add_new_env(env, key, value));
	return (1);
}
