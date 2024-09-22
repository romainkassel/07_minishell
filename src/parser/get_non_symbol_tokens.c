/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_non_symbol_tokens.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: debian <debian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 21:48:22 by rgrochow          #+#    #+#             */
/*   Updated: 2024/09/15 08:37:30 by debian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	is_cmd_arg(t_arg *current, t_shell *shell)
{
	if (current->type[0] == '\0' && current->index > 0
		&& shell->cmd_flag == 1)
	{
		if (current->value[0] == '-')
			ft_strcpy(current->type, "cmd_arg_flag");
		else
			ft_strcpy(current->type, "cmd_arg_fd");
	}
}

void	is_fd(t_arg *current)
{
	if ((current->type[0] == '\0' && current->prev
			&& (ft_strcmp(current->prev->value, "<") == 0
				|| ft_strcmp(current->prev->value, ">>") == 0
				|| ft_strcmp(current->prev->value, ">") == 0))
		|| (is_c(current->value, '/', 0) == SUCCESS
			&& access(current->value, X_OK) != 0
			&& (!current->prev
				|| (current->prev
					&& (ft_strcmp(current->prev->value, "<") == 0
						|| ft_strcmp(current->prev->value, ">") == 0
						|| ft_strcmp(current->prev->value, ">>") == 0
						|| ft_strcmp(current->prev->value, "|") == 0)))))
	{
		ft_strcpy(current->type, "fd");
	}
}

void	is_cmd(t_arg *current, t_shell *shell)
{
	if (current->type[0] == '\0'
		&& (current->index == 0 || ft_strcmp(current->prev->value, "|") == 0
			|| ft_strcmp(current->prev->type, "fd") == 0
			|| ft_strcmp(current->prev->type, "limiter") == 0)
		&& ft_strcmp(current->value, "<") != 0
		&& ft_strcmp(current->value, "<<") != 0
		&& ft_strcmp(current->value, ">") != 0
		&& ft_strcmp(current->value, ">>") != 0
		&& ft_strcmp(current->value, "|") != 0
		&& shell->cmd_flag == 0)
	{
		ft_strcpy(current->type, "cmd");
		shell->cmd_flag = 1;
	}
}

void	is_limiter(t_arg *current, t_shell *shell)
{
	if (current->type[0] == '\0' && current->prev
		&& (ft_strcmp(current->prev->value, "<<") == 0))
	{
		ft_strcpy(current->type, "limiter");
		current->value = ft_strjoin(current->value, 1, "\n", 0);
		if (!current->value)
			exec_exit(shell, NULL, EC_MALLOC_E);
	}
}
