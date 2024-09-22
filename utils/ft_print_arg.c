/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_arg.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkassel <rkassel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 12:38:16 by rgrochow          #+#    #+#             */
/*   Updated: 2024/08/14 16:31:54 by rkassel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_print_arg(t_arg *arg)
{
	t_arg	*current;

	current = arg;
	while (current)
	{
		printf("\n");
		if (current->prev)
			printf("prev->value : %s\n", current->prev->value);
		printf("index : %d\n", current->index);
		printf("type : %s\n", current->type);
		printf("value : %s\n", current->value);
		printf("pipe_scope : %d\n", current->pipe_scope);
		printf("pipe_nb : %d\n", current->pipe_nb);
		printf("quote_status_arg : %d\n", current->quote_status_arg);
		printf("dollar_status_arg : %d\n", current->dollar_status_arg);
		printf("is_builtin : %d\n", current->is_builtin);
		if (current->here_doc)
			printf("here_doc : %s\n", current->here_doc);
		ft_print_double_char(current->arg_lst, "arg_lst");
		printf("cmd_path : %s\n", current->cmd_path);
		if (current->next)
			printf("next->value : %s\n", current->next->value);
		printf("\n");
		current = current->next;
	}
}
