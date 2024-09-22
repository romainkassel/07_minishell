/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_pipes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: debian <debian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 22:13:18 by rgrochow          #+#    #+#             */
/*   Updated: 2024/09/15 08:37:05 by debian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_pipe_index(t_shell *shell, t_arg *cur_cmd, char *std)
{
	t_arg	*current;
	int		pipe_index;

	pipe_index = 0;
	current = shell->arg;
	while (current && current->index <= cur_cmd->index)
	{
		if (ft_strcmp(current->value, "|") == 0)
			pipe_index++;
		current = current->next;
	}
	if (ft_strcmp(std, "in") == 0)
		return (pipe_index - 1);
	else
		return (pipe_index);
}

void	free_pipe_fd(t_shell *shell)
{
	int	i;

	i = 0;
	while (i < shell->pipe_count)
		free(shell->pipe_fd[i++]);
	free(shell->pipe_fd);
}

void	close_pipe_fd(t_shell *shell)
{
	int	i;

	if (shell->pipe_count == 0)
		return ;
	i = 0;
	while (i < shell->pipe_count)
	{
		if (shell->pipe_fd[i][0] != -1)
		{
			close(shell->pipe_fd[i][0]);
			shell->pipe_fd[i][0] = -1;
		}
		if (shell->pipe_fd[i][1] != -1)
		{
			close(shell->pipe_fd[i][1]);
			shell->pipe_fd[i][1] = -1;
		}
		i++;
	}
}

void	get_pipe_count(t_shell *shell)
{
	t_arg	*current;

	current = shell->arg;
	while (current)
	{
		if (ft_strcmp(current->value, "|") == 0)
			shell->pipe_count++;
		current = current->next;
	}
}

void	init_pipes(t_shell *shell)
{
	int	i;

	if (shell->pipe_count == 0)
		return ;
	shell->pipe_fd = (int **)ft_calloc(sizeof(int *), shell->pipe_count);
	if (!shell->pipe_fd)
		exec_exit(shell, NULL, EC_MALLOC_E);
	i = 0;
	while (i < shell->pipe_count)
	{
		shell->pipe_fd[i] = (int *)ft_calloc(sizeof(int), 2);
		if (pipe(shell->pipe_fd[i]) == -1)
			(perror("Pipe"), exec_exit(shell, NULL, EC_MALLOC_E));
		i++;
	}
}
