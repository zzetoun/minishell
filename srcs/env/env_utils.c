/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzetoun <zzetoun@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 18:22:52 by zzetoun           #+#    #+#             */
/*   Updated: 2025/04/29 20:38:32 by zzetoun          ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../include/minishell.h"

size_t ft_darray_len(char **str)
{
    size_t  size;
    
    size = 0;
    if (!str || !*str)
        return (0);
    while(str[size])
        size++;
    return (size);
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
        if (envp->idx < env->size && envp->str)
        {
            str[envp->idx] = ft_strdup(envp->str);
            if (!str[envp->idx])
                return (ft_free_array(str), NULL);   
        }
        envp = envp->next;
    }
    return (str);
}

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
