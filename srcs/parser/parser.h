/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igorsergeevic <igorsergeevic@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 17:41:34 by zzetoun           #+#    #+#             */
/*   Updated: 2025/06/07 03:12:57 by igorsergeev      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

#include "../../include/struct_mini.h"
#include "../../include/minishell.h"


//                                               UTILITIES                                                            //

/*
 * This part of parser.h - is about utilities for commands
*/
t_command			*get_last_cmd(t_command *cmd);
bool				add_back_cmd(t_command **list, t_command *new_node);
t_command	        *add_new_cmd(bool value);
void				clear_cmd(t_command **lst, void (*del)(void *));


/*
 * This part of parser.h - is about utilities for expanding the environment or
 * replacing variables in the command line
*/
char                *setup_env_in_line(char *line, t_data *data);
char                *ft_strndup(const char *s, size_t n);
bool                 has_quotes(const char *str);
bool                has_unclosed_quotes(const char *line);
char				*ft_replace_substr(const char *str, const char *target, const char *replacement);
void 				setup_last_exit_code(t_command *cmd, int last_exit_code);
char				**append_arg(char **args, const char *arg);
void				free_split(char **split);
char				**minishell_split(char *input);
bool				validate_input(const char *input);

//                                             END OF UTILITIES                                                       //

//                                      REDIRECTION AND HEREDOC SETUP                                                 //
void 				setup_truncate(t_io_fds *io);
void				setup_input(t_io_fds *io);
void			 	close_exists_red_fds(t_io_fds *fds);
void			 	setup_append(t_io_fds *io);
void				parse_heredoc(t_data *data, t_command **last_cmd);
bool				fill_heredoc(t_data *data, t_io_fds *io, int fd);
void				list_clear_cmd(t_command **list, void (*del)(void *));
bool				setup_token_type_and_give_command(t_command *cmd, const char *str, enum e_token_types token_type);
bool				setup_heredoc_into_cmd(t_data **data, t_command **cmd,
							   char **split, int *i);
void				parse_pipe(t_command **head);
bool				setup_pipe_into_cmd(t_data **data, t_command **cmd);
bool	setup_word_into_cmd(t_data **data, t_command **cmd, char *word);



//                                      END OF REDIRECTION AND HEREDOC SETUP                                          //

//                                              TOKENIZATION                                                          //
enum e_token_types  get_current_token_type(const char *str);
void                add_back_cmd_token_type(t_command **cmd, t_command *new_node, enum e_token_types token_type);

//											  TOKENIZATION END                                                        //

//                                              MASTER FUNCTION                                                       //
bool                cmd_args_split(t_data *data, char *input);
#endif
