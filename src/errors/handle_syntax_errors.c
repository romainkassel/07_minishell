/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_syntax_errors.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkassel <rkassel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 04:08:34 by debian            #+#    #+#             */
/*   Updated: 2024/09/11 17:09:26 by rkassel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_token(char *current_next_value)
{
	if (ft_strcmp(current_next_value, ">") == 0
		|| ft_strcmp(current_next_value, ">>") == 0
		|| ft_strcmp(current_next_value, "<") == 0
		|| ft_strcmp(current_next_value, "<<") == 0)
	{
		return (SUCCESS);
	}
	return (FAILURE);
}

int	is_fd_or_lim_existing(t_arg *current, t_shell *shell)
{
	if (is_token(current->value) == SUCCESS)
	{
		if (!current->next)
		{
			print_err_mess(E_SYNT_ERR, "newline", "'", shell);
			return (FAILURE);
		}
		else if (current->next && (is_token(current->next->value) == SUCCESS
				|| ft_strcmp(current->next->value, "|") == 0))
		{
			print_err_mess(E_SYNT_ERR, current->next->value, "'", shell);
			return (FAILURE);
		}
	}
	return (SUCCESS);
}

int	is_pipe_filled(t_arg *current, t_shell *shell)
{
	if (ft_strcmp(current->value, "|") == 0)
	{
		if (!current->prev
			|| (current->next && ft_strcmp(current->next->value, "|") == 0))
		{
			print_err_mess(E_SYNT_ERR, current->value, "'", shell);
			return (FAILURE);
		}
		else if (!current->next)
		{
			print_err_mess(E_SYNT_ERR, "newline", "'", shell);
			return (FAILURE);
		}
	}
	return (SUCCESS);
}

int	handle_syntax_errors(t_shell *shell)
{
	t_arg	*current;

	current = shell->arg;
	while (current)
	{
		if (is_fd_or_lim_existing(current, shell) == FAILURE
			|| is_pipe_filled(current, shell) == FAILURE)
		{
			return (FAILURE);
		}
		current = current->next;
	}
	return (SUCCESS);
}
