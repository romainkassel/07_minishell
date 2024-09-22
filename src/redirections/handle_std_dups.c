/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_std_dups.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: debian <debian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 11:27:42 by debian            #+#    #+#             */
/*   Updated: 2024/09/15 08:39:14 by debian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	dup_stdin_to_infile(t_shell *shell, char *filename)
{
	int		fd;
	int		dup_infile;

	fd = open_fd(filename, "O", shell);
	if (fd == -1)
		return ;
	dup_infile = dup2(fd, 0);
	if (dup_infile == -1)
	{
		perror("Dup2");
		exec_exit(shell, NULL, EC_DUP_E);
	}
	close(fd);
}

void	dup_stdin_to_fd0(t_shell *shell, t_arg *cur_cmd)
{
	int	dup_fd0;
	int	stdin_pipe_index;

	stdin_pipe_index = get_pipe_index(shell, cur_cmd, "in");
	dup_fd0 = dup2(shell->pipe_fd[stdin_pipe_index][0], 0);
	if (dup_fd0 == -1)
	{
		perror("Dup2");
		exec_exit(shell, NULL, EC_DUP_E);
	}
}

void	dup_stdout_to_outfile(t_shell *shell, char *outfile, char *symbol)
{
	int	fd;
	int	dup_outfile;

	if (ft_strcmp(symbol, ">") == 0)
		fd = open_fd(outfile, "WR T C", shell);
	else
		fd = open_fd(outfile, "WR A C", shell);
	if (fd == -1)
		exec_exit(shell, NULL, EC_FD_E);
	dup_outfile = dup2(fd, 1);
	if (dup_outfile == -1)
	{
		perror("Dup2");
		exec_exit(shell, NULL, EC_DUP_E);
	}
	close(fd);
}

void	dup_stdout_to_fd1(t_shell *shell, t_arg *cur_cmd)
{
	int	dup_fd1;
	int	stdout_pipe_index;

	stdout_pipe_index = get_pipe_index(shell, cur_cmd, "out");
	dup_fd1 = dup2(shell->pipe_fd[stdout_pipe_index][1], 1);
	if (dup_fd1 == -1)
	{
		perror("Dup2");
		exec_exit(shell, NULL, EC_DUP_E);
	}
}
