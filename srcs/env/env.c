/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzetoun <zzetoun@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 18:22:32 by zzetoun           #+#    #+#             */
/*   Updated: 2025/04/21 20:31:36 by zzetoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void linked_list_print(t_env_info  *env, char **_envp)
{
    t_envp *envp;
    int    idx;

    envp = env->head;
    idx = 0;
   ft_printf(1, "env size: {%d}\n",env->size);
    while(envp)
    {
        ft_printf(1, "[%d] envp->str: {%s}\n",envp->idx, envp->str);
        ft_printf(1, "[%d] _envp: {%s}\n", idx, _envp[idx]);
        idx++;
        envp = envp->next;
    }
}

int ft_env_setup(t_env_info *env, char **envp)
{
    t_envp	*new_env;
    size_t  idx;

    idx = -1;
    env->tail = NULL;
	while (envp[++idx])
	{
		new_env = ft_calloc(1, sizeof(t_envp));
		if (!new_env)
			return (ft_free_env(env));
		if (idx == 0)
			env->head = new_env;
		new_env->idx = idx;
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
    t_envp  *envp;

    envp = env->head;
    if (!data->env)
        data->env = ft_calloc(env->size, sizeof(char *));
    if (!data->env)
        return (0);
    while(envp)
    {
        data->env[envp->idx] = ft_calloc(ft_strlen(envp->str), sizeof(char));
        if (!data->env[envp->idx])
            return (ft_free_array(data->env), 0);
        data->env[envp->idx] = ft_strdup(envp->str);
        envp = envp->next;
    }
    return (1);
}
