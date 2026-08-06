/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamelnyk <mamelnyk@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/02 20:53:19 by mamelnyk          #+#    #+#             */
/*   Updated: 2026/08/06 21:20:39 by mamelnyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "minishell.h"

// exec_ast.c
void			execute_parsed(t_ast_node *ast, t_shell *shell);
t_exec_status	execute_node(t_ast_node *ast, t_shell *shell);

// exec_command.c
t_exec_status	execute_command(t_command *command, t_shell *shell);

// exec_heredoc.c
t_exec_status	run_heredoc_in_child(char *target_str, t_cmd_io *cmd_io,
					t_shell *shell);

// exec_builtin.c
t_exec_status	execute_builtin_command(t_our_command *our_command, char **argv,
					t_cmd_io *cmd_io, t_shell *shell);

// exec_redirection.c
int				handle_redirections(t_redirect_node *redirects,
					t_cmd_io *cmd_io, t_shell *shell);

// exec_pipe.c
t_exec_status	execute_pipe(t_ast_node *ast, t_shell *shell);

// exec_external.c
void			execute_linux_command(char **argv, t_cmd_io *cmd_io,
					t_shell *shell);
t_exec_status	execute_binary_with_path(char **argv, t_cmd_io *cmd_io,
					t_shell *shell);

// exec_utilities.c
void			update_exit_status(t_shell *shell, int status);
t_our_command	*find_builtin_command(char *command_name, t_shell *shell);
void			change_stream_fd(int fd, int stream_fd);
void			close_fds(int input_fd, int output_fd);

// wildcard_utilities.c
bool			is_directory(const char *path);

#endif
