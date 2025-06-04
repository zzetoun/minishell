//
// Created by iqment on 6/3/25.
//

#include "parser.h"

void free_split(char **split)
{
	if (!split)
		return;
	for (int i = 0; split[i]; i++)
		free(split[i]);
	free(split);
}

char **append_arg(char **args, const char *arg)
{
	int i = 0;
	char **new_args;

	if (!args)
	{
		new_args = malloc(sizeof(char *) * 2);
		new_args[0] = ft_strdup(arg);
		new_args[1] = NULL;
		return new_args;
	}
	while (args[i])
		i++;
	new_args = malloc(sizeof(char *) * (i + 2));
	for (int j = 0; j < i; j++)
		new_args[j] = args[j];
	new_args[i] = ft_strdup(arg);
	new_args[i + 1] = NULL;
	free(args);
	return new_args;
}

t_command			*get_last_cmd(t_command *cmd)
{
	while (cmd && cmd->next)
		cmd = cmd->next;
	return cmd;
}
