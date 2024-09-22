/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_shell.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: debian <debian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 12:21:31 by rgrochow          #+#    #+#             */
/*   Updated: 2024/09/20 05:50:33 by debian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_shell(t_shell *shell)
{
	shell->prompt = NULL;
	shell->input = NULL;
	shell->argv = NULL;
	shell->quote_status_shell = NO_HANDLED;
	shell->dollar_status_shell = NO_HANDLED;
	shell->arg = NULL;
	shell->envp_paths = NULL;
	shell->argc = 0;
	shell->cmd_count = 0;
	shell->child_pid = NULL;
	shell->pipe_count = 0;
	shell->pipe_fd = NULL;
	shell->active_child = 0;
	shell->hd_interrupted = 0;
}

void	free_double_char(char **tab)
{
	int	i;

	i = 0;
	if (tab)
	{
		while (tab[i])
			free(tab[i++]);
		free(tab);
		tab = NULL;
	}
}

void	clean_prompt(t_shell *shell)
{
	(void)shell;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	clean_shell_within_rl(t_shell *shell)
{
	if (shell->input)
		(free(shell->input), shell->input = NULL);
	free_double_char(shell->envp_paths);
	free_double_char(shell->argv);
	del_here_docs(shell);
	free_arg_lst(shell->arg);
	if (shell->child_pid)
		(free(shell->child_pid), shell->child_pid = NULL);
	if (shell->pipe_fd)
	{
		close_pipe_fd(shell);
		(free_pipe_fd(shell), shell->pipe_fd = NULL);
	}
	shell->hd_interrupted = 0;
}

void	clean_shell_out_rl(t_shell *shell)
{
	rl_clear_history();
	free_double_char(shell->envp_cpy);
}
