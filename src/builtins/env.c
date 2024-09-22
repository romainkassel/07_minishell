/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgrochow <staafnet@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 13:42:24 by rgrochow          #+#    #+#             */
/*   Updated: 2024/09/05 02:42:16 by rgrochow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_env(t_shell *shell, int declare, int fd)
{
	int	i;

	if (shell->envp_cpy != NULL)
	{
		i = 0;
		while (shell->envp_cpy[i])
		{
			if (declare == 1)
				ft_putstr_fd("export ", fd);
			ft_putstr_fd(shell->envp_cpy[i], fd);
			ft_putchar_fd('\n', fd);
			i++;
		}
		shell->exit_status = 0;
	}
	else
	{
		shell->exit_status = 1;
		perror("env");
	}
}
