/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirections.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: debian <debian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 11:27:42 by debian            #+#    #+#             */
/*   Updated: 2024/09/15 08:38:53 by debian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_arg	*get_start_pipe(t_arg *cur_cmd)
{
	t_arg	*start_pipe;

	start_pipe = cur_cmd;
	while (start_pipe->prev
		&& ft_strcmp(start_pipe->prev->value, "|") != 0)
	{
		start_pipe = start_pipe->prev;
	}
	return (start_pipe);
}

void	handle_input_redir(t_shell *shell, t_arg *cur_cmd)
{
	t_arg	*end_pipe;

	end_pipe = get_end_pipe(cur_cmd);
	while (end_pipe->prev && ft_strcmp(end_pipe->prev->value, "|") != 0)
	{
		if (ft_strcmp(end_pipe->prev->value, "<") == 0)
			return (dup_stdin_to_infile(shell, end_pipe->value));
		else if (ft_strcmp(end_pipe->prev->value, "<<") == 0)
			return (dup_stdin_to_infile(shell, end_pipe->prev->here_doc));
		else
			end_pipe = end_pipe->prev;
	}
	if (end_pipe->prev && ft_strcmp(end_pipe->prev->value, "|") == 0)
		dup_stdin_to_fd0(shell, cur_cmd);
}

void	handle_output_redir_pipe(t_shell *shell, t_arg *cur_cmd)
{
	t_arg	*s_pipe;
	int		redir_flag;
	int		fd;

	redir_flag = 0;
	s_pipe = get_start_pipe(cur_cmd);
	while (s_pipe && ft_strcmp(s_pipe->value, "|") != 0)
	{
		if (ft_strcmp(s_pipe->value, "<") == 0 && s_pipe->next)
		{
			fd = open_fd(s_pipe->next->value, "O", shell);
			if (fd == -1)
				exec_exit(shell, NULL, EC_FD_E);
			close (fd);
		}
		else if (ft_strcmp(s_pipe->value, ">") == 0
			|| ft_strcmp(s_pipe->value, ">>") == 0)
		{
			redir_flag = 1;
			dup_stdout_to_outfile(shell, s_pipe->next->value, s_pipe->value);
		}
		s_pipe = s_pipe->next;
	}
	if (redir_flag == 0 && s_pipe && ft_strcmp(s_pipe->value, "|") == 0)
		dup_stdout_to_fd1(shell, cur_cmd);
}
