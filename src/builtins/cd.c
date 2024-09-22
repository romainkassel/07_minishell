/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkassel <rkassel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 16:13:46 by rgrochow          #+#    #+#             */
/*   Updated: 2024/09/13 11:33:20 by rkassel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_cd(t_shell *shell, t_arg *cmd)
{
	char	path[1024];

	getcwd(path, sizeof(path));
	ft_strcat(path, "/");
	if (!cmd->arg_lst[1])
		(chdir(getenv("HOME")), shell->exit_status = 0);
	else if (!cmd->arg_lst[2] && chdir(cmd->arg_lst[1]) != 0)
	{
		print_err_mess_cd(cmd->arg_lst[1], ": ", strerror(errno), shell);
		shell->exit_status = 1;
	}
	else if (!cmd->arg_lst[2])
		(ft_strcat(path, cmd->arg_lst[1]), chdir(path), shell->exit_status = 0);
	else if (cmd->arg_lst[2])
	{
		print_err_mess("cd: ", E_MANY_ARG, NULL, shell);
		shell->exit_status = 1;
	}
}
