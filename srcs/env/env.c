/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzetoun <zzetoun@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 18:22:32 by zzetoun           #+#    #+#             */
/*   Updated: 2025/04/25 03:47:40 by zzetoun          ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../include/minishell.h"

int ft_env_setup(t_env_info *env, char **envp)
{
        t_envp	*new_env;
        size_t  idx;

        idx = -1;
        env->tail = NULL;
        while (++idx <= ft_env_len(envp))
        {
            new_env = ft_calloc(1, sizeof(t_envp));
            if (!new_env)
                return (ft_free_env(env), 0);
            if (idx == 0)
                env->head = new_env;
            new_env->idx = idx;
            if (idx < ft_env_len(envp))
                new_env->str = ft_strdup(envp[idx]);
            new_env->next = NULL;
            if (env->tail != NULL)
                env->tail->next = new_env;
            env->tail = new_env;
        }
        env->size = idx;
        return (1);
}

int set_env_value(t_env_info *env, char *term, char *value)
{
    t_envp *envp;

    envp = env->head;
    while (envp)
    {
        if (ft_strncmp(envp->str, term, ft_strlen(term)) == 0)
        {
            ft_free_ptr(envp->str);
            envp->str = ft_strdup(value);
            return (1);
        }
        envp = envp->next;
    }
    if (!envp)
        return (ft_add_env(env, value));
    return (0);
}

char    *get_env_value(t_env_info *env, char *term)
{
    t_envp *envp;

    envp = env->head;
    while (envp)
    {
        if (ft_strncmp(envp->str, term, ft_strlen(term)) == 0)
            return (envp->str);
        envp = envp->next;
    }
    return (NULL);
}

char    **ft_env_to_str(t_env_info *env)
{
    t_envp  *envp;
    char    **str;

    envp = env->head;
    str = ft_calloc(env->size, sizeof(char *));
    if (!str)
        return (0);
    while(envp)
    {
        if (envp->idx < env->size - 1)
        {
            str[envp->idx] = ft_strdup(envp->str);
            if (!str[envp->idx])
                return (ft_free_array(str), NULL);   
        }
        envp = envp->next;
    }
    return (str);
}
