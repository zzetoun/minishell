/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzetoun <zzetoun@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 18:22:32 by zzetoun           #+#    #+#             */
/*   Updated: 2025/05/01 17:22:13 by zzetoun          ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../include/minishell.h"

int ft_env_setup(t_env_info *env, char **envp, size_t  idx)
{
    t_envp	*new_env;

    if (!envp || !*envp)
        return(ft_env_setup_null(env));
    env->tail = NULL;
    while (++idx < ft_darray_len(envp))
    {
        new_env = ft_calloc(1, sizeof(t_envp));
        if (!new_env)
            return (ft_free_env(env), 0);
        if (idx == 0)
            env->head = new_env;
        if (idx < ft_darray_len(envp))
            new_env->str = ft_strdup(envp[idx]);
        new_env->idx = idx;
        new_env->next = NULL;
        if (env->tail != NULL)
            env->tail->next = new_env;
        env->tail = new_env;
    }
    env->size = idx;
    env->shlvl = ft_atoi(get_env(env, "SHLVL"));
    if (env->size <= 4)
        return (set_env(env, "SHLVL=", ft_itoa(env->shlvl + 1)));
    return (1);
}

int  ft_env_setup_null(t_env_info *env)
{
    char    buff[PATH_MAX];

    env->tail = NULL;
    env->size = 0;
    if (!ft_add_new_env(env, "PWD=", getcwd(buff, PATH_MAX)))
        return (0);
    if (!ft_add_new_env(env, "SHLVL=", "1"))
        return (0);
    if (!ft_add_new_env(env, "_=", "/usr/bin/env"))
        return (0);
    return (1);
}

char    *get_env(t_env_info *env, char *key)
{
    t_envp *envp;

    envp = env->head;
    while (envp)
    {
        if (ft_key_cmp(envp->str, key) == 0)
            return ((ft_strchr(envp->str, '=')) + 1);
        envp = envp->next;
    }
    return (NULL);
}

int set_env(t_env_info *env, char *key, char *value)
{
    t_envp *envp;

    envp = env->head;
    while (envp && key)
    {
        if (ft_key_cmp(envp->str, key) == 0)
        {
            ft_free_ptr(envp->str);
            envp->str = ft_strjoin(key, value);
            return (1);
        }
        envp = envp->next;
    }
    ft_add_new_env(env, key, value);
    return (0);
}
