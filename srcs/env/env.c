/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzetoun <zzetoun@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 18:22:32 by zzetoun           #+#    #+#             */
/*   Updated: 2025/04/20 21:49:51 by zzetoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int ft_env_setup(t_env_info *env, char **envp)
{
    t_envp	*new_env;
    size_t  idx;

	env->tail = NULL;
    idx = -1;
	while (envp[++idx])
	{
		new_env = ft_calloc(1, sizeof(t_envp));
		if (!new_env)
			return (ft_free_env(env));
		if (idx == 1)
			env->head = new_env;
		new_env->idx = idx - 1;
        new_env->str = ft_strdup(envp[idx]);
		new_env->next = NULL;
		if (env->tail != NULL)
			env->tail->next = new_env;
		env->tail = new_env;
	}
    env->size = idx;
	env->tail->next = NULL;
    return (1);
}

int    ft_str_to_env(t_data *data, t_env_info *env)
{
    size_t  idx;
    t_envp  *envp;

    idx = -1;
    envp = env->head;
    if (!data->env)
        data->env = ft_calloc(env->size + 1, sizeof(char *));
    if (!data->env)
        return (0);
    while(++idx <= env->size)
    {
        printf("print me 01\n");
        data->env[idx] = ft_calloc(ft_strlen(envp->str), sizeof(char));
        printf("print me 02\n");
        if (!data->env[idx])
            return (ft_free_array(data->env), 0);
        data->env[idx] = ft_strdup(envp->str);
		ft_printf(1, "envp->str: %s\n", envp->str);
		ft_printf(1, "new_envp[%d]: %s\n",idx , data->env[idx]);
        envp = envp->next;
    }
    printf("idx: %zu\n", idx);
    data->env[idx] = "\0";
    return (1);
}
