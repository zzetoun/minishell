#include "parser.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <readline/readline.h>
#include <readline/history.h>

static void	parse_pipe(t_command **head)          /* head == &data->cmd */
{
	t_command *last = get_last_cmd(*head);

	if (!last)                         /* список пуст — сделать первый узел */
	{
		add_back_cmd(head, add_new_cmd(false));
		last = get_last_cmd(*head);
		setup_io(last);
	}
	last->pipe_output = true;

	add_back_cmd(&last, add_new_cmd(false));   /* следующий узел */
	setup_io(last->next);
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

//static bool	setup_heredoc_into_cmd(t_data **data, t_command **cmd, char **split, int *i)
//{
//	if ((*cmd)->io_fds->heredoc_delimiter)
//		ft_free_ptr((*cmd)->io_fds->heredoc_delimiter);
//	(*cmd)->io_fds->heredoc_delimiter = ft_strdup(split[++(*i)]);//TODO
//	if (!(*cmd)->io_fds->heredoc_delimiter)
//		printf("Huita v strdup");
//	(*cmd)->io_fds->heredoc_quotes = has_quotes((*cmd)->io_fds->heredoc_delimiter);
//	parse_heredoc(*data, &(*data)->cmd);
//	if (!(*cmd)->io_fds->heredoc_delimiter)
//	{
//		free_split(split);
//		return (false);
//	}
//	(*cmd)->token_type = HEREDOC;
//	return (true);
//}

static bool	setup_heredoc_into_cmd(t_data **data,
									  t_command **cmd,
									  char **split,
									  int *i)
{
	t_io_fds	*io;

	/* базовая валидация аргументов */
	if (!data || !*data || !cmd || !*cmd || !split || !split[*i] || !split[*i + 1])
		return (false);

	io = (*cmd)->io_fds;

	/* ── 1. если раньше уже был heredoc, чистим всё, чтобы не течь ── */
	if (io->heredoc_delimiter)
	{
		ft_free_ptr(io->heredoc_delimiter);
		if (io->fd_in != -1)          /* read-конец предыдущего pipe-а  */
			close(io->fd_in);
		io->fd_in = -1;
	}

	/* ── 2. сохраняем новый делимитер ────────────────────────────── */
	(*i)++;                                        /* переходим к слову-делимитеру  */
	io->heredoc_delimiter = ft_strdup(split[*i]);
	if (!io->heredoc_delimiter)                    /* strdup не удался              */
		return (false);

	io->heredoc_quotes = has_quotes(io->heredoc_delimiter);

	/* ── 3. читаем собственно heredoc ─────────────────────────────── */
	/* parse_heredoc ждёт &cmd, а не &(*data)->cmd!                   */
	parse_heredoc(*data, cmd);

	/* ── 4. финальные метки ───────────────────────────────────────── */
	(*cmd)->token_type = HEREDOC;
	return (true);
}


bool		cmd_args_split(t_data *data, char *input)
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
    if (!split) {
		ft_free_ptr(input);
		return (false);
	}
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
            parse_pipe(&data->cmd);
            cmd = get_last_cmd(data->cmd);
            setup_io(cmd);
            i++;
            continue;
        }
        cmd = get_last_cmd(data->cmd);
        if (strcmp(split[i], "<") == 0 && split[i+1])
            setup_token_type_and_give_command(cmd, split[++i], INPUT);
        else if (strcmp(split[i], ">") == 0 && split[i+1])
            setup_token_type_and_give_command(cmd, split[++i], TRUNC);
        else if (strcmp(split[i], ">>") == 0 && split[i+1])
            setup_token_type_and_give_command(cmd, split[++i], APPEND);
        else if (strcmp(split[i], "<<") == 0 && split[i + 1])
		{
			if (!setup_heredoc_into_cmd(&data, &cmd, split, &i))
			{
				free_split(split);
				ft_free_ptr(input);
				return (false);
			}
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
