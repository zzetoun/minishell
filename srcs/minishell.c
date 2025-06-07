/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzetoun <zzetoun@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 19:22:17 by zzetoun           #+#    #+#             */
/*   Updated: 2025/05/07 19:22:17 by zzetoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

    int last_exit_code;

    last_exit_code = 1;
    while (1)
    {
        set_signals_interactive();
        data->user_input = readline(PROMPT);
		if (!data->user_input) // move this inside validate
		{
			ft_printf(1, "\n");
			exit_full(data, g_final_exit_code);
		}
		add_history(data->user_input);
		if (!validate_input(data->user_input)) {
			ft_free_dptr((void *)&data->user_input);
			continue;
		}
        set_signals_noninteractive();
        if (cmd_args_split(data, data->user_input))
        {
            g_final_exit_code = execute(data);
            last_exit_code = g_final_exit_code;
        }
        else
            g_final_exit_code = last_exit_code;
        ft_printf(1, ">> g_final_exit_code : [%d] <<\n", g_final_exit_code);
		ft_freedom(&data, false);
    }
}

void	minishell_noninteractive(t_data *data, char *arg)
{
	char	**user_inputs;
	int		 i;
	int		 last_exit_code;

	user_inputs = ft_split(arg, ';');
	if (!user_inputs)
		exit_full(data, EXIT_FAILURE);
	last_exit_code = 1;
	i = -1;
	while (user_inputs[++i])
	{
		data->user_input = ft_strtrim(user_inputs[i], " \t\n");
		set_signals_noninteractive();
		if (cmd_args_split(data, data->user_input))
		{
			g_final_exit_code = execute(data);
			last_exit_code = g_final_exit_code;
		}
		else
			g_final_exit_code = last_exit_code;
		ft_printf(1, ">> g_final_exit_code : [%d] <<\n", g_final_exit_code);
	}
	ft_free_array(user_inputs);
}

/* main:
*	Begins minishell. Checks input and determines if
*	minishell should be run interactively or not.
*/

int	main(int ac, char **av, char **envp)
{
	t_data		data;
	t_env_info	env;

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
