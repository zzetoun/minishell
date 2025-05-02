#include "../include/minishell.h"

void linked_list_print(t_env_info  *env, char **_envp, int option)
{
    t_envp *envp;
    int    idx;

    envp = env->head;
    idx = 0;
    ft_printf(1, "env size: {%d}\n", env->size);
    ft_printf(1, "env shlvl: {%d}\n", env->shlvl);
    while(envp)
    {
        if (option == 2 && _envp)
        {
            ft_printf(1, "[%d] envp->str: {%s}\n",envp->idx, envp->str);
            ft_printf(1, "[%d] _envp: {%s}\n", idx, _envp[idx]);
        }
        else if (option == 1)
            ft_printf(1, "[%d] envp->str: {%s}\n",envp->idx, envp->str);
        else if (option == 0)
            ft_printf(1, "[%d] _envp: {%s}\n", idx, _envp[idx]);
        else
            break ;
        idx++;
        envp = envp->next;
    }
    printf("last envp %p\n", envp);
}