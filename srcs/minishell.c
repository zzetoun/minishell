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

char *ft_replace_substr(const char *str, const char *target, const char *replacement)
{
    if (!str || !target || !replacement)
        return NULL;

    size_t str_len = strlen(str);
    size_t target_len = strlen(target);
    size_t repl_len = strlen(replacement);

    // Подсчёт количества вхождений
    size_t count = 0;
    const char *tmp = str;
    while ((tmp = strstr(tmp, target)))
    {
        count++;
        tmp += target_len;
    }

    if (count == 0)
        return strdup(str);

    // Выделение памяти под новую строку
    size_t new_len = str_len - (count * target_len) + (count * repl_len);
    char *result = malloc(new_len + 1);
    if (!result)
        return NULL;

    // Замена
    const char *src = str;
    char *dst = result;

    while (*src)
    {
        if (strncmp(src, target, target_len) == 0)
        {
            memcpy(dst, replacement, repl_len);
            dst += repl_len;
            src += target_len;
        }
        else
        {
            *dst++ = *src++;
        }
    }

    *dst = '\0';
    return result;
}
//static void     print_tokenezation(t_data *data)
//{
//    t_command *current;
//
//    current = data->cmd;
//    while (current)
//    {
//        int tt = current->token_type;
//        char **args = current->args;
//        char *cmd = current->command;
//        switch (tt) {
//            case WORD:
//                printf("Token Type: WORD\nCommand: %s, Args: ", cmd);
//                for (int i = 0; args && args[i]; i++)
//                    printf("%s ", args[i]);
//                printf("\n");
//                break;
//            case PIPE:
//                printf("Token Type: PIPE\n");
//                break;
//            case INPUT:
//                printf("Token Type: INPUT\nInfile: %s\n", current->io_fds->infile);
//                break;
//            case TRUNC:
//                printf("Token Type: TRUNC\nOutfile: %s\n", current->io_fds->outfile);
//                break;
//            case APPEND:
//                printf("Token Type: APPEND\nOutfile: %s\n", current->io_fds->outfile);
//                break;
//            case HEREDOC:
//                printf("Token Type: HEREDOC\nDelimiter: %s\n", current->io_fds->heredoc_delimiter);
//                break;
//            default:
//                printf("Unknown Token Type: %d\n", tt);
//                break;
//        }
//        current = current->next;
//    }
//    return ;
//}


void	minishell_interactive(t_data *data)
{

    int last_exit_code;

    last_exit_code = 0;
    while (1)
    {
        data->user_input = readline(PROMPT);
        if (cmd_args_split(data, data->user_input))
        {
            t_command *cmd = data->cmd;
            char *exit_str = ft_itoa(last_exit_code);
            while (cmd)
            {
                for (int i = 0; cmd->args && cmd->args[i]; i++)
                {
                    if (strstr(cmd->args[i], "$?"))
                    {
                        char *new = ft_replace_substr(cmd->args[i], "$?", exit_str);
                        free(cmd->args[i]);
                        cmd->args[i] = new;
                    }
                }
                cmd = cmd->next;
            }
//            print_tokenezation(data);
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
        ft_freedom(data, false);
        ft_free_cmds(data);
        ft_free_cmds(data);
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
