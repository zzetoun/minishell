/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzetoun <zzetoun@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 22:49:15 by zzetoun           #+#    #+#             */
/*   Updated: 2025/05/06 22:49:15 by zzetoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	set_export(t_env_info *env, char *arg)
{
	char	*s;
	int		result;

	result = 0;
	if (ft_strlen(ft_strchr(arg, '=')) >= 1)
	{
		s = ft_substr(arg, 0, ft_strlen(arg) - ft_strlen(ft_strchr(arg, '=')));
		if (ft_strlen(ft_strchr(arg, '=')) == 1)
		{
			if (!env_key(env, s))
				result = set_env(env, s, NULL);
			else
				result = add_new_env(env, s, "");
		}
		else
			result = set_env(env, s, ft_strchr(arg, '=') + 1);
		free(s);
	}
	else if (env_key(env, arg))
		result = add_new_env(env, arg, NULL);
	return (result);
}

static char	**ft_env_to_export(t_envp *en, size_t size)
{
	char	**s;

	s = ft_calloc(size + 1, sizeof(char *));
	if (!s)
		return (NULL);
	while (en)
	{
		if (ft_strchr(en->str, '='))
		{
			s[en->idx] = ft_strjoin(en->key, "=\"");
			s[en->idx] = ft_strjoin_free(s[en->idx], en->value);
			s[en->idx] = ft_strjoin_free(s[en->idx], "\"");
		}
		else
			s[en->idx] = ft_strdup(en->key);
		en = en->next;
	}
	return (s);
}

int	export_args_check(char *arg, char *cmd)
{
	int	i;

	if (!arg || (!ft_isalpha(arg[0]) && arg[0] != '_' && !ft_isspace(arg[0])))
		return (errmsg(cmd, arg, MINIERID, EXIT_FAILURE));
	else if (str_compare(cmd, "unset") && ft_strchr(arg, '='))
		return (errmsg(cmd, arg, MINIERID, EXIT_FAILURE));
	i = -1;
	while (arg[++i])
	{
		if (arg[i] == '=' && str_compare(cmd, "export"))
			break ;
		else if (!ft_isalnum(arg[i]) && arg[i] != '_' && ft_isspace(arg[i]))
			return (errmsg(cmd, arg, MINIERID, EXIT_FAILURE));
	}
	return (0);
}

static void	export_print(char **envp, size_t size)
{
	size_t	idx;
	size_t	jdx;
	char	*tmp;

	idx = -1;
	tmp = NULL;
	while (++idx < size)
	{
		jdx = idx;
		while (++jdx < size)
		{
			if (ft_strncmp(envp[idx], envp[jdx], -1) > 0)
			{
				tmp = envp[idx];
				envp[idx] = envp[jdx];
				envp[jdx] = tmp;
			}
		}
	}
	idx = -1;
	while (envp[++idx])
		ft_printf(1, "declare -x %s\n", envp[idx]);
	ft_free_array(envp);
}

int	ft_export(t_env_info *env, char **args)
{
	char	**envp;
	char	*arg;
	int		error;

	error = 0;
	envp = ft_env_to_export(env->head, env->size);
	if (!envp)
		return (error);
	if (!args || !*args)
		export_print(envp, env->size);
	while (args && *args)
	{
		arg = *args;
		error = export_args_check(arg, "export");
		if (!error)
			error = set_export(env, arg);
		args++;
	}
	return (error);
}
