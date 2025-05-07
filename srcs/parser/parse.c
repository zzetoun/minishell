
#include "parser.h"

//TOKENS: << >> < > | & && $ $? ; ' " \ ( )

// static char **get_tokens_list(void)
// {
//	 char	**tokens;

//	 tokens = (char **)malloc(sizeof(char *) * 16);
//	 // <<
//	 tokens[0] = (char *)malloc(sizeof(char) * 3);
//	 tokens[0] = "<<\0";
//	 // >>
//	 tokens[1] = (char *)malloc(sizeof(char) * 3);
//	 tokens[1] = ">>\0";
//	 // <
//	 tokens[2] = (char *)malloc(sizeof(char) * 2);
//	 tokens[0] = "<\0";

// }

void	serealyze_tokens(int	current, char *arg, t_token **token)
{
	if (current < 0)
		return;
	if (!arg)
		return;
	if (!token)
		return;
	return;
}

int	parse_tokens(int	argc, char **argv, t_token **tokens)
{
	if (argc < 0)
		return (0);
	if (!argv)
		return (0);
	if (!tokens)
		return (0);
	return (1);
}

void	cmd_args_split(t_command *cmd, char *input)
{
	char	*args;
	int	 idx;

	args = ft_strchr(input, ' ');
	ft_printf(1, "args: {%s}\n", args);
	cmd->command = ft_substr(input, 0, ft_strlen(input) - ft_strlen(args));
	ft_printf(1, "cmd: {%s}\n", cmd->command);
	cmd->args = ft_split(args, ' ');
	idx = -1;
	while (cmd->args && cmd->args[++idx])
		ft_printf(1, "arg[%d]= {%s}\n", idx, cmd->args[idx]);
}
