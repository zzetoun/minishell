//
// Created by IqMent on 17.05.2025.
//

#include "minishell.h"

enum e_token_types  get_current_token_type(const char *current)
{
    if (*current == '|')
        return (PIPE);
    else if (*current == '<' && current[1] == '<')
        return (HEREDOC);
    else if (*current == '>' && current[1] == '>')
        return (APPEND);
    else if (*current == '>')
        return (TRUNC);
    else if (*current == '<')
        return (INPUT);
    else if (*current == ' ')
        return (SPACES);
    else if (*current == '$')
        return (VAR);
    else if (*current == '\0')
        return (END);
    return (WORD);
}

//bool tokenize_input(t_data *data, const char *input) {
//    size_t i = 0;
//    t_command *current_cmd = NULL;
//
//    if (!input || !*input || !data)
//        return false;
//
//    while (input[i] != '\0') {
//        enum e_token_types token_type = get_current_token_type(&input[i]);
//
//        if (token_type == PIPE) {
//            add_back_cmd(&data->cmd, add_new_cmd(true));
//            current_cmd = last_cmd(data->cmd);
//            setup_io(current_cmd);
//            i++;
//        } else if (token_type == INPUT || token_type == TRUNC || token_type == APPEND || token_type == HEREDOC) {
//            // Handle redirections
//            if (!current_cmd) {
//                add_back_cmd(&data->cmd, add_new_cmd(false));
//                current_cmd = last_cmd(data->cmd);
//                setup_io(current_cmd);
//            }
//            if (token_type == INPUT && input[i + 1]) {
//                current_cmd->io_fds->infile = ft_strdup(&input[++i]);
//            } else if ((token_type == TRUNC || token_type == APPEND) && input[i + 1]) {
//                current_cmd->io_fds->outfile = ft_strdup(&input[++i]);
//            } else if (token_type == HEREDOC && input[i + 1]) {
//                current_cmd->io_fds->heredoc_delimiter = ft_strdup(&input[++i]);
//                current_cmd->io_fds->heredoc_quotes = has_quotes(current_cmd->io_fds->heredoc_delimiter);
//            }
//            i++;
//        } else if (token_type == WORD) {
//            if (!current_cmd) {
//                add_back_cmd(&data->cmd, add_new_cmd(false));
//                current_cmd = last_cmd(data->cmd);
//                setup_io(current_cmd);
//            }
//            if (!current_cmd->command) {
//                current_cmd->command = ft_strdup(&input[i]);
//                current_cmd->args = append_arg(current_cmd->args, &input[i]);
//            } else {
//                current_cmd->args = append_arg(current_cmd->args, &input[i]);
//            }
//            while (input[i] != ' ' && input[i] != '\0' && input[i] != '|' && input[i] != '<' && input[i] != '>') {
//                i++;
//            }
//        } else {
//            i++;
//        }
//    }
//    return (true);
//}
static void	ensure_cmd(t_data *data, t_command **current_cmd)
{
	if (!*current_cmd)
	{
		add_back_cmd(&data->cmd, add_new_cmd(false));
		*current_cmd = last_cmd(data->cmd);
		setup_io(*current_cmd);
	}
}

/* -------------------------------------------------------------------------- */
/*  Handle the pipe symbol ("|")                                               */
/* -------------------------------------------------------------------------- */
static size_t	process_pipe(t_data *data, t_command **current_cmd,
			 size_t i)
{
	add_back_cmd(&data->cmd, add_new_cmd(true));
	*current_cmd = last_cmd(data->cmd);
	setup_io(*current_cmd);
	return (i + 1);
}

/* -------------------------------------------------------------------------- */
/*  Handle redirections (<, >, >>, <<)                                        */
/* -------------------------------------------------------------------------- */
static size_t	process_redirection(t_data *data, t_command **current_cmd,
					const char *input, size_t i)
{
	enum e_token_types   type;

	type = get_current_token_type(&input[i]);
	ensure_cmd(data, current_cmd);
	if (type == INPUT && input[i + 1])
		(*current_cmd)->io_fds->infile = ft_strdup(&input[++i]);
	else if ((type == TRUNC || type == APPEND) && input[i + 1])
		(*current_cmd)->io_fds->outfile = ft_strdup(&input[++i]);
	else if (type == HEREDOC && input[i + 1])
	{
		(*current_cmd)->io_fds->heredoc_delimiter = ft_strdup(&input[++i]);
		(*current_cmd)->io_fds->heredoc_quotes =
				has_quotes((*current_cmd)->io_fds->heredoc_delimiter);
	}
	return (i + 1);
}

/* -------------------------------------------------------------------------- */
/*  Handle regular words (command / arguments)                                */
/* -------------------------------------------------------------------------- */
static size_t	process_word(t_data *data, t_command **current_cmd,
							  const char *input, size_t i)
{
	size_t  j;

	j = i;
	ensure_cmd(data, current_cmd);
	while (input[j] && input[j] != ' ' && input[j] != '|' &&
		   input[j] != '<' && input[j] != '>')
		j++;
	if (!(*current_cmd)->command)
		(*current_cmd)->command = ft_substr(input, i, j - i);
	(*current_cmd)->args = append_arg((*current_cmd)->args, &input[i]);
	return (j);
}

/* -------------------------------------------------------------------------- */
/*  Public API: tokenize the raw user input                                   */
/* -------------------------------------------------------------------------- */
bool	tokenize_input(t_data *data, const char *input)
{
	size_t          i;
	t_command       *current_cmd;
	enum e_token_types   type;

	i = 0;
	current_cmd = NULL;
	if (!input || !*input || !data)
		return (false);
	while (input[i] != '\0')
	{
		type = get_current_token_type(&input[i]);
		if (type == PIPE)
			i = process_pipe(data, &current_cmd, i);
		else if (type == INPUT || type == TRUNC || type == APPEND ||
				 type == HEREDOC)
			i = process_redirection(data, &current_cmd, input, i);
		else if (type == WORD)
			i = process_word(data, &current_cmd, input, i);
		else
			i++;
	}
	return (true);
}
