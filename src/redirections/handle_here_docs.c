/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_here_docs.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: debian <debian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 11:27:42 by debian            #+#    #+#             */
/*   Updated: 2024/09/20 05:52:28 by debian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	open_fd(char *fd_name, char *options, t_shell *shell)
{
	int	fd;

	fd = 0;
	if (ft_strcmp(options, "WR T C") == 0)
		fd = open(fd_name, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	else if (ft_strcmp(options, "WR A C") == 0)
		fd = open(fd_name, O_WRONLY | O_APPEND | O_CREAT, 0644);
	else if (ft_strcmp(options, "O") == 0)
		fd = open(fd_name, O_RDONLY);
	if (fd == -1)
	{
		shell->exit_status = 1;
		print_err_mess(fd_name, ": ", strerror(errno), shell);
	}
	return (fd);
}

void	del_here_docs(t_shell *shell)
{
	t_arg	*current;

	current = shell->arg;
	while (current)
	{
		if (current->here_doc)
		{
			if (shell->active_child == 0)
			{
				if (unlink(current->here_doc) == -1)
					perror("Unlink");
			}
			free(current->here_doc);
			current->here_doc = NULL;
		}
		current = current->next;
	}
}

int	get_here_doc_input(t_shell *shell, t_arg *current)
{
	int		fd;
	char	*tmp;
	char	*limiter;

	current->here_doc = ft_strjoin("here_doc", 0, ft_itoa(current->index), 1);
	if (!current->here_doc)
		exec_exit(shell, NULL, EC_MALLOC_E);
	fd = open_fd(current->here_doc, "WR T C", shell);
	if (fd == -1)
		return (EC_FD_E);
	tmp = ft_get_next_line(STDIN_FILENO);
	if (!tmp)
		return (close(fd), shell->hd_interrupted = 1, EC_HD_E);
	limiter = current->next->value;
	if (ft_strcmp(tmp, limiter) != 0)
		ft_putstr_fd(tmp, fd);
	while (ft_strcmp(tmp, limiter) != 0)
	{
		(free(tmp), tmp = ft_get_next_line(STDIN_FILENO));
		if (!tmp)
			break ;
		if (ft_strcmp(tmp, limiter) != 0)
			ft_putstr_fd(tmp, fd);
	}
	return (free(tmp), close(fd), EC_SUCCESS);
}

void	handle_here_docs(t_shell *shell)
{
	t_arg	*current;

	current = shell->arg;
	while (current)
	{
		if (ft_strcmp(current->value, "<<") == 0
			&& (shell->hd_interrupted == 0
				|| (shell->hd_interrupted == 1 && g_signal_value != 2)))
		{
			get_here_doc_input(shell, current);
		}
		current = current->next;
	}
}
