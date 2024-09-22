/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_builtins.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: debian <debian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 16:13:46 by rgrochow          #+#    #+#             */
/*   Updated: 2024/09/15 08:24:01 by debian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_builtin(t_arg *cmd, t_shell *shell, int output_fd)
{
	if (ft_strcmp(cmd->value, "echo") == 0)
		exec_echo(shell, cmd, output_fd);
	else if (ft_strcmp(cmd->value, "cd") == 0)
		exec_cd(shell, cmd);
	else if (ft_strcmp(cmd->value, "pwd") == 0)
		exec_pwd(shell, output_fd);
	else if (ft_strcmp(cmd->value, "export") == 0)
		exec_export(shell, cmd, output_fd);
	else if (ft_strcmp(cmd->value, "unset") == 0)
		exec_unset(shell, cmd);
	else if (ft_strcmp(cmd->value, "env") == 0)
		exec_env(shell, 0, output_fd);
	else if (ft_strcmp(cmd->value, "exit") == 0)
		exec_exit(shell, cmd, EC_SUCCESS);
	if (output_fd != 1)
		close(output_fd);
}

t_arg	*get_end_pipe(t_arg *cur_cmd)
{
	t_arg	*end_pipe;

	end_pipe = cur_cmd;
	while (end_pipe->next && ft_strcmp(end_pipe->next->value, "|") != 0)
		end_pipe = end_pipe->next;
	return (end_pipe);
}

int	check_fd(char *filename, char *open_mode, t_shell *shell)
{
	int		fd;

	fd = 0;
	if (ft_strcmp(open_mode, "O") == 0)
		fd = open_fd(filename, "O", shell);
	else if (ft_strcmp(open_mode, "WR T C") == 0)
		fd = open_fd(filename, "WR T C", shell);
	else if (ft_strcmp(open_mode, "WR A C") == 0)
		fd = open_fd(filename, "WR A C", shell);
	if (fd == -1)
		return (FAILURE);
	close (fd);
	return (SUCCESS);
}

int	check_inv_fds(t_arg *single_cmd, t_shell *shell)
{
	t_arg	*s_pipe;

	s_pipe = get_start_pipe(single_cmd);
	while (s_pipe && ft_strcmp(s_pipe->value, "|") != 0)
	{
		if (((ft_strcmp(s_pipe->value, "<") == 0 && s_pipe->next)
				&& (check_fd(s_pipe->next->value, "O", shell) == FAILURE))
			|| ((ft_strcmp(s_pipe->value, ">") == 0 && s_pipe->next)
				&& (check_fd(s_pipe->next->value, "WR T C", shell) == FAILURE))
			|| ((ft_strcmp(s_pipe->value, ">>") == 0 && s_pipe->next)
				&& (check_fd(s_pipe->next->value, "WR A C", shell) == FAILURE)))
		{
			return (FAILURE);
		}
		else if (ft_strcmp(s_pipe->type, "fd") == 0
			&& access(s_pipe->value, F_OK) != 0)
		{
			print_err_mess(s_pipe->value, ": ", strerror(errno), shell);
			return (FAILURE);
		}
		s_pipe = s_pipe->next;
	}
	return (SUCCESS);
}

int	handle_output_redir_builtin(t_arg *single_cmd, t_shell *shell)
{
	t_arg	*end_pipe;

	end_pipe = get_end_pipe(single_cmd);
	while (end_pipe)
	{
		if (ft_strcmp(end_pipe->value, ">") == 0)
			return (open_fd(end_pipe->next->value, "WR T C", shell));
		else if (ft_strcmp(end_pipe->value, ">>") == 0)
			return (open_fd(end_pipe->next->value, "WR A C", shell));
		end_pipe = end_pipe->prev;
	}
	return (1);
}
