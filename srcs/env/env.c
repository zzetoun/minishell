/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzetoun <zzetoun@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 18:22:32 by zzetoun           #+#    #+#             */
/*   Updated: 2025/04/27 18:44:17 by zzetoun          ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../include/minishell.h"

int ft_add_new_env(t_env_info *env, char *key, char *value)
{
    t_envp	*new_env;
    
    new_env = env->head;
	while (new_env->next)
        new_env = new_env->next;
    new_env = ft_calloc(1, sizeof(t_envp));
    if (!new_env)
        return (ft_free_env(env), 0);
    if (env->size == 1)
        env->head = new_env;
    new_env->idx = env->size;
    if (value)
        new_env->str = ft_strjoin(key, value);
    new_env->next = NULL;
    if (env->tail != NULL)
        env->tail->next = new_env;
    env->tail = new_env;
    env->tail->next = NULL;
    env->size++;
    return (1);
}

int set_env(t_env_info *env, char *key, char *value)
{
    t_envp *envp;

    envp = env->head;
    while (envp)
    {
        if (ft_strncmp(envp->str, key, ft_strlen(key)) == 0)
        {
            ft_free_ptr(envp->str);
            envp->str = ft_strjoin(key, value);
            return (1);
        }
        envp = envp->next;
    }
    if (!envp)
        return (ft_add_new_env(env, key, value));
    return (0);
}
int ft_env_setup(t_env_info *env, char **envp)
{
        t_envp	*new_env;
        size_t  idx;

        idx = -1;
        if (!envp || !*envp)
            return(ft_env_setup_null(env, idx));
        env->tail = NULL;
        while (++idx <= ft_env_len(envp))
        {
            new_env = ft_calloc(1, sizeof(t_envp));
            if (!new_env)
                return (ft_free_env(env), 0);
            if (idx == 0)
                env->head = new_env;
            new_env->idx = idx;
            if (idx < ft_env_len(envp) && envp && *envp)
                new_env->str = ft_strdup(envp[idx]);
            new_env->next = NULL;
            if (env->tail != NULL)
                env->tail->next = new_env;
            env->tail = new_env;
        }
        env->size = idx;
        env->shlvl = ft_atoi(get_env(env, "SHLVL"));
        return (1);
}

int  ft_env_setup_null(t_env_info *env, size_t idx)
{
    t_envp	*new_env;
    char    buff[PATH_MAX];

    env->tail = NULL;
    while(++idx < 3)
    {
        new_env = ft_calloc(1, sizeof(t_envp));
        if (!new_env)
            return (ft_free_env(env), 0);
        if (idx == 0)
            env->head = new_env;
        new_env->idx = idx;
        if (idx == 0 && getcwd(buff, PATH_MAX))
            new_env->str = ft_strjoin("PWD=", getcwd(buff, PATH_MAX));
        else if (idx == 1)
            new_env->str = ft_strdup("SHLVL=1"); // need to figure out how to increase the number
        else if (idx == 2)
            new_env->str = ft_strdup("_=/usr/bin/env");
        new_env->next = NULL;
        if (env->tail != NULL)
            env->tail->next = new_env;
        env->tail = new_env;
    }
    env->size = idx;
    return (1);
}

char    *get_env(t_env_info *env, char *key)
{
    t_envp *envp;

    envp = env->head;
    while (envp)
    {
        if (ft_strncmp(envp->str, key, ft_strlen(key)) == 0)
            return ((ft_strchr(envp->str, '=')) + 1);
        envp = envp->next;
    }
    return (NULL);
}
