/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzetoun <zzetoun@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 18:22:52 by zzetoun           #+#    #+#             */
/*   Updated: 2025/04/21 19:53:24 by zzetoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int ft_add_env_node(t_env_info *env, t_envp *envp, char *value)
{
    envp = ft_calloc(1, sizeof(t_envp));
    if (!envp)
        return (ft_free_env(env), 0);
    envp->idx++;
    envp->str = ft_strdup(value);
    envp->next = NULL;
    if (env->tail != NULL)
         env->tail->next = envp;
    env->tail = envp;
    env->size++;
    env->tail->next = NULL;
    return (1);
}

size_t ft_env_len(char **envp)
{
    size_t  size;
    
    size = 0;
    if (!envp || !*envp)
        return (0);
    while(envp[size])
        size++;
    return (size);
}

int ft_free_env(t_env_info *env)
{
	t_envp	*list;

	list = env->head;
	while (list)
	{
		list = list->next;
		env->head->idx = 0;
        free(env->head->str);
		free(env->head);
		env->head = list;
	}
    env->size = 0;
    return (0);
}

char    *get_env_value(t_env_info *env, char *term)
{
    t_envp *envp;

    envp = env->head;
    while (envp)
    {
        if (ft_strncmp(envp->str, term, ft_stlen(term)) == 0)
            return (envp->str);
        envp = envp->next;
    }
    return (NULL);
}

int set_env_value(t_env_info *env, char *term, char *value)
{
    t_envp *envp;

    envp = env->head;
    while (envp)
    {
        if (ft_strncmp(envp->str, term, ft_stlen(term)) == 0)
        {
                free(envp->str);
                envp->str = ft_strdup(value);
        }
        envp = envp->next;
    }
    if (!envp)
        return (ft_add_env_node(env, envp, value));
    return (1);
}
