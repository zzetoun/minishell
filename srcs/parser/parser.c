//
// Created by IqMent on 09.05.2025.
//

#include "parser.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <readline/readline.h>
#include <readline/history.h>

static void	parse_pipe(t_command **cmd, t_token **token_lst) // <--- t_token **token_lst is optional
{
    t_command	*last_cmd;
    last_cmd = get_last_cmd(*cmd);
    last_cmd->pipe_output = 1;
    add_back_cmd(&last_cmd, add_new_cmd(0));
    if (token_lst && *token_lst)
        *token_lst = (*token_lst)->next; // <-- go to the next token, unless you go to the next one outside
}

static void setup_token_type_and_give_command(t_command *cmd, const char *str, enum e_token_types token_type)
{
	if (!cmd || !str)
		return ;
	cmd->token_type = token_type;
	if (token_type == INPUT)
		cmd->io_fds->infile = ft_strdup(str);
	else if (token_type == TRUNC)
		cmd->io_fds->outfile = ft_strdup(str);
	else if (token_type == APPEND)
		cmd->io_fds->append_file = ft_strdup(str);
	else
		printf("Error: Unknown token type %d\n", token_type);

}

bool	cmd_args_split(t_data *data, char *input)
{
    char	**split;
    int		i;
    t_command *cmd;


    if (!input || !*input || !data)
		return (false);
	add_history(input);
	cmd = data->cmd;
    input = setup_env_in_line(input, data);
    split = minishell_split(input);
    if (!split)
        return (false);
    i = 0;
    while (split[i])
    {
        if (!cmd)
        {
            add_back_cmd(&data->cmd, add_new_cmd(false));
            cmd = get_last_cmd(data->cmd);
            setup_io(cmd);
        }
        if (strcmp(split[i], "|") == 0)
        {
            parse_pipe(&data->cmd, NULL);
            cmd = get_last_cmd(data->cmd);
            setup_io(cmd);
            i++;
            continue;
        }
        cmd = get_last_cmd(data->cmd);
        if (strcmp(split[i], "<") == 0 && split[i+1])
            setup_token_type_and_give_command(cmd, split[++i], INPUT);
			//cmd->io_fds->infile = ft_strdup(split[++i]);
        else if (strcmp(split[i], ">") == 0 && split[i+1])
            setup_token_type_and_give_command(cmd, split[++i], TRUNC);
			//cmd->io_fds->outfile = ft_strdup(split[++i]);
        else if (strcmp(split[i], ">>") == 0 && split[i+1])
            setup_token_type_and_give_command(cmd, split[++i], APPEND);
			//cmd->io_fds->append_file = ft_strdup(split[++i]);
        else if (strcmp(split[i], "<<") == 0 && split[i+1])
        {
            cmd->io_fds->heredoc_delimiter = ft_strdup(split[++i]);
            cmd->io_fds->heredoc_quotes = has_quotes(cmd->io_fds->heredoc_delimiter);
			parse_heredoc(data, &data->cmd);
			if (!cmd->io_fds->heredoc_delimiter)
			{
				free_split(split);
				return (false);
			}
			cmd->token_type = HEREDOC;
		}
        else
		{
            if (cmd && !cmd->command)
            {
                cmd->token_type = WORD;
                cmd->command = ft_strdup(split[i]);
                cmd->args = append_arg(cmd->args, split[i]);
            }
            else {
                cmd->args = append_arg(cmd->args, split[i]);
            }
        }
        i++;
    }
    free_split(split);
	ft_free_ptr(input);
    return (true);
}
