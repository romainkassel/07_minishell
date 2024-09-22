/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_it.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgrochow <staafnet@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 22:13:18 by rgrochow          #+#    #+#             */
/*   Updated: 2024/09/18 21:06:46 by rgrochow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include "minishell.h"

void	init_child_pid(t_shell *shell)
{
	shell->child_pid = (pid_t *)ft_calloc(sizeof(pid_t),
			(shell->pipe_count + 1));
	if (!shell->child_pid)
		exec_exit(shell, NULL, EC_MALLOC_E);
}

void	wait_children(t_shell *shell, int *status)
{
	int	i;

	i = 0;
	while (i < (shell->pipe_count + 1))
	{
		waitpid(shell->child_pid[i++], status, 0);
		shell->exit_status = WEXITSTATUS(*status);
	}
}

void	pipe_it(t_shell *shell)
{
	int		i;
	int		status;
	t_arg	*cur_cmd;

	i = 0;
	while (i < (shell->pipe_count + 1))
	{
		shell->child_pid[i] = fork();
		if (shell->child_pid[i] == -1)
			(perror("Fork"), exec_exit(shell, NULL, EC_FORK_E));
		if (shell->child_pid[i] == 0)
		{
			shell->active_child = 1;
			cur_cmd = get_cmd(shell, i);
			if (check_inv_fds(cur_cmd, shell) == FAILURE)
				exec_exit(shell, NULL, EC_FD_E);
			handle_output_redir_pipe(shell, cur_cmd);
			handle_input_redir(shell, cur_cmd);
			close_pipe_fd(shell);
			exec_cmd(shell, cur_cmd);
		}
		i++;
	}
	close_pipe_fd(shell);
	wait_children(shell, &status);
}
