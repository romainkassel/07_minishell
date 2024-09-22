/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkassel <rkassel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 21:48:22 by rgrochow          #+#    #+#             */
/*   Updated: 2024/09/16 12:35:32 by rkassel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	dissociate_args(t_shell *shell)
{
	t_arg	*current;
	int		i;

	current = shell->arg;
	while (current)
	{
		if (current->quote_status_arg == NO_HANDLED)
		{
			i = 0;
			while (current->value[i])
			{
				if (current->value[i + 1] != '\0'
					&& ft_strlen(current->value) > 2
					&& is_double_symbol(current, i) == 0)
					i = add_new_node(shell, current, i, 2);
				else if (ft_strlen(current->value) > 1
					&& is_single_symbol(current, i) == 0)
					i = add_new_node(shell, current, i, 1);
				i++;
			}
		}
		current = current->next;
	}
}

int	parse_input(t_shell *shell, char *input)
{
	store_input(shell, input);
	init_arg_with_value(shell);
	dissociate_args(shell);
	if (handle_syntax_errors(shell) == FAILURE)
		return (FAILURE);
	tokenize_input(shell);
	handle_here_docs(shell);
	return (SUCCESS);
}
