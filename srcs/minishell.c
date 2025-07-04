/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzetoun <zzetoun@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 19:22:17 by zzetoun           #+#    #+#             */
/*   Updated: 2025/06/04 03:24:58 by zzetoun          ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../include/minishell.h"

int	g_final_exit_code;

/* first_check:
*	Checks the arguments at program start up. Minishell can start either:
*		* when no arguments are supplied.
*		* when the -c option is supplied followed by one argument.
*	Returns true if minishell can begin, false with a usage message if not.
*/
static bool	first_check(t_data *data, int ac, char **av)
{
	if (ac != 1 && ac != 3)
		return (how_to_message(false));
	if (ac == 3)
	{
		data->interactive = false;
		if (!av[1] || (av[1] && !str_compare(av[1], "-c")))
			return (how_to_message(false));
		else if (!av[2] || (av[2] && av[2][0] == '\0'))
			return (how_to_message(false));
	}
	else
		data->interactive = true;
	return (true);
}

/* minishell_interactive:
*	Runs parsing and execution in interactive mode, i.e. when minishell
*	is started without arguments and provides a prompt for user input.
*/
void	minishell_interactive(t_data *data)
{
	int	exit_code_tmp;

	exit_code_tmp = 1;
	while (1)
	{
		set_signals_interactive();
		data->user_input = readline(PROMPT);
		set_signals_noninteractive();
		if (parse_user_input(data))
		{
			g_final_exit_code = execute(data);
			exit_code_tmp = g_final_exit_code;
		}
		else
			g_final_exit_code = exit_code_tmp;
		ft_freedom(data, false);
	}
}

/* minishell_noninteractive:
*	Runs parsing and execution in noninteractive mode, i.e. when
*	minishell is started with the -c option followed by an argument
*	containing the commands to be executed:
*		./minishell -c "echo hello | wc -c"
*	Commands in this mode can be separated by a semicolon, ';' to
*	indicate sequential execution:
*		./minishell -c "echo hello; ls"
*	-> echo hello is the first command run
*	-> ls is the second
*/
void	minishell_noninteractive(t_data *data, char *arg)
{
	char	**user_inputs;
	int		idx;
	int	exit_code_tmp;

	exit_code_tmp = 1;
	user_inputs = ft_split(arg, ';');
	if (!user_inputs)
		exit_full(data, EXIT_FAILURE);
	idx = -1;
	while (user_inputs[++idx])
	{
		data->user_input = ft_strdup(user_inputs[idx]);
		if (parse_user_input(data))
		{
			g_final_exit_code = execute(data);
			exit_code_tmp = g_final_exit_code;
		}
		else
			g_final_exit_code = exit_code_tmp;
	}
	ft_free_array(user_inputs);
}

static void	welcome_msg(void)
{
	ft_printf(1, "\n\t###############################\n");
	ft_printf(1, "\t#                             #\n");
	ft_printf(1, "\t#  Minishell by Zorz & Igor   #\n");
	ft_printf(1, "\t#                             #\n");
	ft_printf(1, "\t###############################\n\n");
}

/* main:
*	Begins minishell. Checks input and determines if
*	minishell should be run interactively or not.
*	Exits the shell with the exit status or the last command.
*/
int	main(int ac, char **av, char **envp)
{
	t_data		data;
	t_env_info	env;

	welcome_msg();
	ft_memset(&data, 0, sizeof(t_data));
	data.env = &env;
	if (!first_check(&data, ac, av) || !setup_mini(&data, envp))
		exit_full(NULL, EXIT_FAILURE);
	if (data.interactive)
		minishell_interactive(&data);
	else
		minishell_noninteractive(&data, av[2]);
	exit_full(&data, g_final_exit_code);
	return (0);
}
