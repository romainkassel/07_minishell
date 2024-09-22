/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_dollar_question_mark.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgrochow <staafnet@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 21:48:22 by rgrochow          #+#    #+#             */
/*   Updated: 2024/09/20 01:03:45 by rgrochow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_exit_code(t_shell *shell)
{
	char	*exit_code;

	if (g_signal_value == 2)
	{
		shell->exit_status = 130;
		g_signal_value = 0;
	}
	else if (g_signal_value == 3)
	{
		shell->exit_status = 131;
		g_signal_value = 0;
	}
	exit_code = ft_itoa(shell->exit_status);
	if (!exit_code)
		exec_exit(shell, NULL, EC_MALLOC_E);
	return (exit_code);
}
