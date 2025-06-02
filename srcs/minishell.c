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

#include "../include/minishell.h"

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

static bool	mini_setup_mini(t_data *data)
{
    data->token = NULL;
    data->user_input = NULL;
    data->cmd = NULL;
    data->pid = -1;
    errno = 0;
    g_final_exit_code = 0;
    return (true);
}

static void ft_free_cmds(t_data *data)
{
    t_command *command;

    command = data->cmd;
    while (command)
    {
        free(command->command);
        ft_free_array(command->args);
        if (command->io_fds)
        {
            free(command->io_fds->infile);
            free(command->io_fds->outfile);
            free(command->io_fds->heredoc_delimiter);
            free(command->io_fds);
        }
        t_command *next_command = command->next;
        free(command);
        command = next_command;
    }
    mini_setup_mini(data);
}

/* minishell_interactive:
*	Runs parsing and execution in interactive mode, i.e. when minishell
*	is started without arguments and provides a prompt for user input.
*/

void	minishell_interactive(t_data *data)
{

    int last_exit_code;

    last_exit_code = 0;
    while (1)
    {
        set_signals_interactive();
        data->user_input = readline(PROMPT);
        set_signals_noninteractive();
        if (cmd_args_split(data, data->user_input))
        {
            char *exit_str = ft_itoa(last_exit_code);
            setup_last_exit_code(data->cmd, last_exit_code);
            free(exit_str);
            g_final_exit_code = execute(data);
            last_exit_code = g_final_exit_code;
        }
        else
        {
            g_final_exit_code = 1;
            last_exit_code = 1;
        }
        ft_printf(1, ">> g_final_exit_code : [%d] <<\n", g_final_exit_code);
        ft_free_cmds(data);
    }
}


//void	minishell_interactive(t_data *data)
//{
//	while (1)
//	{
//		set_signals_interactive();
//		data->user_input = readline(PROMPT);
//		add_history(data->user_input); // ---->>> should be moved inside parsing after parsing is chechked <<<-----
//		set_signals_noninteractive();
//		if (cmd_args_split(data, data->user_input)) // -->>>>> parsing is here  <<<<<----
//		{
//
//			g_final_exit_code = execute(data);
//		}
//		else
//			g_final_exit_code = 1;
//		ft_printf(1, ">> g_final_exit_code : [%d] <<\n", g_final_exit_code);
//		ft_freedom(data, false);
//	}
//}


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

	user_inputs = ft_split(arg, ';');
	if (!user_inputs)
		exit_full(data, EXIT_FAILURE);
	idx = -1;
	while (user_inputs[++idx])
	{
		data->user_input = ft_strdup(user_inputs[idx]);
		if (cmd_args_split(data, data->user_input)) // -->>>>> parsing is here  <<<<<----
            execute(data);
//			g_final_exit_code = execute(data);
//		else
//			g_final_exit_code = 1;
		ft_freedom(data, false);
	}
	ft_free_array(user_inputs);
}

static void	welcome_msg(void)
{
	printf("\n\t###############################\n");
	printf("\t#                             #\n");
	printf("\t#  Minishell by Zorz & Igor   #\n");
	printf("\t#                             #\n");
	printf("\t###############################\n\n");
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
