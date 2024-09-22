/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgrochow <staafnet@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 16:55:48 by rgrochow          #+#    #+#             */
/*   Updated: 2024/09/18 18:01:38 by rgrochow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_numeric_arg(char *cur_cmd_arg_lst_1)
{
	int	i;

	if (ft_isdigit(cur_cmd_arg_lst_1[0]) == FAILURE
		&& cur_cmd_arg_lst_1[0] != '-')
	{
		return (FAILURE);
	}
	i = 1;
	while (cur_cmd_arg_lst_1[i])
	{
		if (ft_isdigit(cur_cmd_arg_lst_1[i]) == FAILURE)
			return (FAILURE);
		i++;
	}
	if (ft_atollu(cur_cmd_arg_lst_1) > LONG_MAX)
		return (FAILURE);
	return (SUCCESS);
}

void	handle_exit_with_arg(char *cur_cmd_arg_lst_1, t_shell *shell)
{
	int	exit_code;

	if (cur_cmd_arg_lst_1[0] != '-'
		&& ft_atollu(cur_cmd_arg_lst_1) <= 255)
	{
		exit_code = ft_atollu(cur_cmd_arg_lst_1);
	}
	else if (cur_cmd_arg_lst_1[0] == '-')
	{
		if (ft_atollu(cur_cmd_arg_lst_1 + 1) <= 255)
		{
			exit_code = 256 - ft_atollu(cur_cmd_arg_lst_1 + 1);
		}
		else
			exit_code = 256 - (ft_atollu(cur_cmd_arg_lst_1 + 1) % 256);
	}
	else
		exit_code = ft_atollu(cur_cmd_arg_lst_1) % 256;
	exec_exit(shell, NULL, exit_code);
}

void	handle_exit_arg(t_arg *cur_cmd, t_shell *shell)
{
	if (is_numeric_arg(cur_cmd->arg_lst[1]) == FAILURE)
	{
		if (shell->active_child == 0)
		{
			printf("exit\n");
			print_err_mess("exit: ", cur_cmd->arg_lst[1], E_NUM_ARG_REQ, shell);
			(clean_shell_within_rl(shell), clean_shell_out_rl(shell), exit(2));
		}
		if (shell->active_child == 1)
		{
			print_err_mess("exit: ", cur_cmd->arg_lst[1], E_NUM_ARG_REQ, shell);
			exec_exit(shell, NULL, 2);
		}
	}
	else if (cur_cmd->arg_lst[2])
	{
		if (shell->active_child == 0)
			(printf("exit\n"), shell->exit_status = 1);
		print_err_mess("exit: ", "too many arguments", NULL, shell);
		if (shell->active_child == 1)
			exec_exit(shell, NULL, 1);
	}
	else
		handle_exit_with_arg(cur_cmd->arg_lst[1], shell);
}

void	exec_exit(t_shell *shell, t_arg *cur_cmd, int exit_code)
{
	if (cur_cmd && cur_cmd->arg_lst[1])
		handle_exit_arg(cur_cmd, shell);
	else
	{
		if (shell->active_child == 0)
		{
			clean_shell_out_rl(shell);
			printf("exit\n");
		}
		else
		{
			free_double_char(shell->envp_cpy);
			rl_clear_history();
		}
		clean_shell_within_rl(shell);
		exit(exit_code);
	}
}
