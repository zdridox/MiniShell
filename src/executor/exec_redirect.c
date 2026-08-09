/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirect.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamelnyk <mamelnyk@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/03 18:12:42 by mamelnyk          #+#    #+#             */
/*   Updated: 2026/08/09 20:29:55 by mamelnyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

static int	hendle_redirect_out(t_redirect_node *redirect, t_cmd_io *cmd_io)
{
	if (cmd_io->input_fd != STDIN_FILENO)
		close(cmd_io->input_fd);
	cmd_io->input_fd = open(redirect->target_str, O_RDONLY);
	if (cmd_io->input_fd < 0)
	{
		cmd_io->input_fd = STDIN_FILENO;
		close_fds(cmd_io->input_fd, cmd_io->output_fd);
		display_error_message("Failed to open input file");
		return (ERROR);
	}
	return (SUCCESS);
}

static int	handle_redirect_in(t_redirect_node *redirect, t_cmd_io *cmd_io)
{
	if (cmd_io->output_fd != STDOUT_FILENO)
		close(cmd_io->output_fd);
	cmd_io->output_fd = open(redirect->target_str,
			O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (cmd_io->output_fd < 0)
	{
		cmd_io->output_fd = STDOUT_FILENO;
		close_fds(cmd_io->input_fd, cmd_io->output_fd);
		display_error_message("Failed to open output file");
		return (ERROR);
	}
	return (SUCCESS);
}

static int	handle_redirect_append(t_redirect_node *redirect, t_cmd_io *cmd_io)
{
	if (cmd_io->output_fd != STDOUT_FILENO)
		close(cmd_io->output_fd);
	cmd_io->output_fd = open(redirect->target_str,
			O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (cmd_io->output_fd < 0)
	{
		cmd_io->output_fd = STDOUT_FILENO;
		close_fds(cmd_io->input_fd, cmd_io->output_fd);
		display_error_message("Failed to open output file");
		return (ERROR);
	}
	return (SUCCESS);
}

static int	handle_redirect_heredoc(t_redirect_node *redirect, t_cmd_io *cmd_io,
		t_shell *shell)
{
	if (cmd_io->input_fd != STDIN_FILENO)
		close(cmd_io->input_fd);
	if (run_heredoc_in_child(redirect->target_str,
			cmd_io, shell) == EXEC_FAILURE)
	{
		cmd_io->input_fd = STDIN_FILENO;
		close_fds(cmd_io->input_fd, cmd_io->output_fd);
		return (ERROR);
	}
	return (SUCCESS);
}

int	handle_redirections(t_redirect_node *redirects, t_cmd_io *cmd_io,
		t_shell *shell)
{
	int	status;

	status = SUCCESS;
	while (redirects != NULL)
	{
		if (redirects->type == REDIRECT_IN)
			status = hendle_redirect_out(redirects, cmd_io);
		else if (redirects->type == REDIRECT_OUT)
			status = handle_redirect_in(redirects, cmd_io);
		else if (redirects->type == REDIRECT_APPEND)
			status = handle_redirect_append(redirects, cmd_io);
		else if (redirects->type == REDIRECT_HEREDOC)
			status = handle_redirect_heredoc(redirects, cmd_io, shell);
		if (status == ERROR)
			return (ERROR);
		redirects = redirects->next;
	}
	return (SUCCESS);
}
