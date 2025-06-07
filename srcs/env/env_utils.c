/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzetoun <zzetoun@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 22:49:37 by zzetoun           #+#    #+#             */
/*   Updated: 2025/05/06 22:49:37 by zzetoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*get_env(t_env_info *env, char *key)
{
	t_envp	*envp;

	envp = env->head;
	while (envp)
	{
		if (str_compare(envp->key, key))
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
			ft_free_dptr(envp->value);
			envp->value = ft_strdup(value);
			ft_free_dptr(envp->str);
			envp->str = ft_strjoin(key, "=");
			envp->str = ft_strjoin_free(envp->str, value);
			return (0);
		}
		envp = envp->next;
	}
	return (add_new_env(env, key, value));
}
int	env_key(t_env_info *env, char *key)
{
	t_envp	*envp;

	envp = env->head;
	while (envp)
	{
		if (ft_strncmp(envp->key, key, ft_strlen(key)) == 0)
			return (0);
		envp = envp->next;
	}
	return (1);
}

char	**env_tostr(t_env_info *env)
{
	t_envp	*envp;
	char	**str;
	int		idx;

	str = ft_calloc(env->size + 1, sizeof(char *));
	if (!str)
		return (0);
	idx = -1;
	envp = env->head;
	while (envp)
	{
		if (ft_strchr(envp->str, '='))
		{
			str[++idx] = ft_strdup(envp->str);
			if (!str[idx])
				return (ft_free_array(str), NULL);
		}
		envp = envp->next;
	}
	if (idx == -1)
		return (ft_free_array(str), NULL);
	return (str);
}

int	add_new_env(t_env_info *env, char *key, char *value)
{
	t_envp	*new_env;
	t_envp	*current;

	new_env = ft_calloc(1, sizeof(t_envp));
	if (!new_env)
		return (free_env(env), errmsg(NULL, NULL, strerror(errno), errno));
	new_env->idx = env->size;
	if (key || value)
		ft_set_key_value(new_env, NULL, key, value);
	new_env->next = NULL;
	if (env->head == NULL)
		env->head = new_env;
	else
	{
		current = env->head;
		while (current->next)
			current = current->next;
		current->next = new_env;
	}
	env->size++;
	return (0);
}
