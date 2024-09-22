/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_and_dollar_utils.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkassel <rkassel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 21:48:22 by rgrochow          #+#    #+#             */
/*   Updated: 2024/09/10 17:49:14 by rkassel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	incr_s_quote_flag(char *argv_i, int j, int d_quote, int s_quote)
{
	if (argv_i[j] == '\'' && d_quote % 2 == 0
		&& (s_quote % 2 == 1 || (s_quote % 2 == 0
				&& is_c(argv_i, '\'', j + 1) == SUCCESS)))
	{
		return (SUCCESS);
	}
	else
		return (FAILURE);
}

int	incr_d_quote_flag(char *argv_i, int j, int d_quote, int s_quote)
{
	if (argv_i[j] == '"' && s_quote % 2 == 0
		&& (d_quote % 2 == 1 || (d_quote % 2 == 0
				&& is_c(argv_i, '"', j + 1) == SUCCESS)))
	{
		return (SUCCESS);
	}
	else
		return (FAILURE);
}

int	should_dollar_be_exp(char *argv_i, int j, int s_quote)
{
	if (argv_i[j] == '$' && s_quote % 2 == 0 && argv_i[j + 1]
		&& argv_i[j + 1] != '|')
	{
		return (SUCCESS);
	}
	else
		return (FAILURE);
}

void	update_dollar_flag(char *exp_argv_i, t_shell *shell)
{
	if (ft_strcmp(exp_argv_i, "") == 0)
		shell->dollar_status_shell = HANDLED_BUT_EMPTY;
	else
		shell->dollar_status_shell = HANDLED;
}

void	get_dollar_and_quote_status(t_arg *new_node, t_shell *shell)
{
	if (shell->quote_status_shell == HANDLED)
		new_node->quote_status_arg = HANDLED;
	else
		new_node->quote_status_arg = NO_HANDLED;
	if (shell->dollar_status_shell == HANDLED)
		new_node->dollar_status_arg = HANDLED;
	else
		new_node->dollar_status_arg = NO_HANDLED;
}
