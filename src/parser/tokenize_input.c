/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkassel <rkassel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 21:48:22 by rgrochow          #+#    #+#             */
/*   Updated: 2024/09/11 17:22:39 by rkassel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_symbol_tokens(t_arg *current, t_shell *shell)
{
	if (ft_strcmp(current->value, "<") == 0)
		ft_strcpy(current->type, "single_input_redir");
	else if (ft_strcmp(current->value, ">") == 0)
		ft_strcpy(current->type, "single_output_redir");
	else if (ft_strcmp(current->value, "<<") == 0)
		ft_strcpy(current->type, "double_input_redir");
	else if (ft_strcmp(current->value, ">>") == 0)
		ft_strcpy(current->type, "double_output_redir");
	else if (ft_strcmp(current->value, "|") == 0)
	{
		ft_strcpy(current->type, "single_pipe");
		shell->cmd_flag = 0;
	}
	else if (ft_strcmp(current->value, "$?") == 0)
		ft_strcpy(current->type, "dollar_question_mark");
}

void	get_tokens(t_arg *current, t_shell *shell)
{
	get_symbol_tokens(current, shell);
	is_fd(current);
	is_limiter(current, shell);
	is_cmd(current, shell);
	is_cmd_arg(current, shell);
}

int	get_pipe_scope(t_arg *current, int pipe_scope_flag)
{
	if (ft_strcmp(current->value, "|") == 0)
		current->pipe_nb = pipe_scope_flag++;
	if (ft_strcmp(current->type, "cmd") == 0)
		current->pipe_scope = pipe_scope_flag;
	return (pipe_scope_flag);
}

void	tokenize_input(t_shell *shell)
{
	t_arg	*current;
	int		i;
	int		pipe_scope_flag;

	current = shell->arg;
	i = 0;
	pipe_scope_flag = 0;
	shell->cmd_flag = 0;
	while (current)
	{
		current->index = i++;
		get_tokens(current, shell);
		pipe_scope_flag = get_pipe_scope(current, pipe_scope_flag);
		current = current->next;
	}
}
