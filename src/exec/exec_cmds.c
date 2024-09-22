/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: debian <debian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 22:13:18 by rgrochow          #+#    #+#             */
/*   Updated: 2024/09/20 06:02:14 by debian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_cmd_count(t_shell *shell)
{
	t_arg	*current;

	current = shell->arg;
	while (current)
	{
		if (ft_strcmp(current->type, "cmd") == 0)
			shell->cmd_count++;
		current = current->next;
	}
}

void	exec_cmd(t_shell *shell, t_arg *cur_cmd)
{
	if (cur_cmd->is_builtin == 1)
	{
		exec_builtin(cur_cmd, shell, 1);
		exec_exit(shell, NULL, EC_SUCCESS);
	}
	else if (cur_cmd->cmd_path)
	{
		if (execve(cur_cmd->cmd_path, cur_cmd->arg_lst, shell->envp_cpy) == -1)
		{
			ft_putstr_fd(cur_cmd->cmd_path, 2);
			ft_putchar_fd('\n', 2);
			perror("Execve");
			exec_exit(shell, NULL, EC_CMD_E);
		}
	}
	else
	{
		if (ft_strcmp(cur_cmd->type, "cmd") == 0)
			print_err_mess(cur_cmd->value, E_UNEX_CMD, NULL, shell);
		if (shell->hd_interrupted == 1)
			exec_exit(shell, NULL, EC_SUCCESS);
		else
			exec_exit(shell, NULL, EC_CMD_E);
	}
}

t_arg	*get_pipe(t_shell *shell, int i)
{
	t_arg	*pipe;

	pipe = shell->arg;
	while (pipe)
	{
		if (ft_strcmp(pipe->value, "|") == 0 && pipe->pipe_nb == (i - 1))
			return (pipe);
		pipe = pipe->next;
	}
	return (NULL);
}

t_arg	*get_cmd(t_shell *shell, int i)
{
	t_arg	*cmd;

	cmd = shell->arg;
	while (cmd)
	{
		if (cmd->pipe_scope == i && ft_strcmp(cmd->type, "cmd") == 0)
			return (cmd);
		cmd = cmd->next;
	}
	if (i == 0)
		return (shell->arg);
	else
	{
		cmd = get_pipe(shell, i);
		if (cmd->next)
			return (cmd->next);
	}
	return (NULL);
}

void	exec_cmds(t_shell *shell)
{
	t_arg	*single_cmd;
	int		output_fd;

	get_envp_paths(shell);
	get_cmd_data(shell);
	get_pipe_count(shell);
	get_cmd_count(shell);
	single_cmd = get_cmd(shell, 0);
	if (shell->pipe_count == 0 && shell->cmd_count == 0)
	{
		if (shell->arg && check_inv_fds(shell->arg, shell) == FAILURE)
			return ;
	}
	else if (shell->pipe_count == 0 && single_cmd->is_builtin == 1)
	{
		if (check_inv_fds(single_cmd, shell) == FAILURE)
			return ;
		output_fd = handle_output_redir_builtin(single_cmd, shell);
		if (output_fd == -1)
			return ;
		exec_builtin(single_cmd, shell, output_fd);
	}
	else
		(init_child_pid(shell), init_pipes(shell), pipe_it(shell));
	del_here_docs(shell);
}
