/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzetoun <zzetoun@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 22:58:21 by zzetoun           #+#    #+#             */
/*   Updated: 2025/06/07 18:42:25 by zzetoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	ft_indxing(t_env_info *env)
{
	t_envp	*envp;
	int		idx;

	envp = env->head;
	idx = 0;
	if (!envp)
		return ;
	while (envp)
	{
		envp->idx = idx;
		envp = envp->next;
		idx++;
	}
	env->size = idx;
}

static void	free_env_in(t_env_info *env, char *key)
{
	t_envp	*envp;
	t_envp	*tmp;
	t_envp	*pre;

	envp = env->head;
	while (envp)
	{
		if (str_compare(envp->key, key) && !str_compare("_", key))
		{
			tmp = envp;
			free(tmp->str);
			free(tmp->key);
			free(tmp->value);
			tmp->idx = -1;
			if (envp->next)
				pre->next = envp->next;
			else
				pre->next = NULL;
			ft_free_dptr((void **)&tmp);
			ft_indxing(env);
			break ;
		}
		pre = envp;
		envp = envp->next;
	}
}

int	ft_unset(t_env_info *env, char **args)
{
	int	idx;

	idx = 1;
	if (!args || !*args || !args[idx])
		return (1);
	while (args[idx])
	{
		if (!export_args_check(args[idx], "unset"))
			free_env_in(env, args[idx]);
		idx++;
	}
	return (1);
}
