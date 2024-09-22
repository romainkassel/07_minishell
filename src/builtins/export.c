/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkassel <rkassel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 19:01:41 by rgrochow          #+#    #+#             */
/*   Updated: 2024/09/16 16:43:59 by rkassel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_id_valid(char *cmd_arg, t_shell *shell)
{
	if (ft_isalpha(cmd_arg[0]) == FAILURE)
	{
		print_err_mess(E_EXPORT, cmd_arg, E_UNV_ID, shell);
		return (FAILURE);
	}
	return (SUCCESS);
}

void	update_var(t_shell *shell, t_arg *cur_cmd, int var_index, int i)
{
	free(shell->envp_cpy[var_index]);
	shell->envp_cpy[var_index] = ft_strdup(cur_cmd->arg_lst[i]);
	if (!shell->envp_cpy[var_index])
		exec_exit(shell, NULL, EC_MALLOC_E);
}

void	add_var(t_shell *shell, t_arg *cur_cmd, int i)
{
	char	**new_envp_cpy;
	int		envp_len;
	int		j;

	envp_len = get_envp_len(shell->envp_cpy);
	new_envp_cpy = (char **)ft_calloc(sizeof(char *), (envp_len + 2));
	if (!new_envp_cpy)
		exec_exit(shell, NULL, EC_MALLOC_E);
	j = 0;
	while (shell->envp_cpy[j])
	{
		new_envp_cpy[j] = ft_strdup(shell->envp_cpy[j]);
		if (!new_envp_cpy[j])
			(free_double_char(new_envp_cpy),
				exec_exit(shell, NULL, EC_MALLOC_E));
		j++;
	}
	new_envp_cpy[j] = ft_strdup(cur_cmd->arg_lst[i]);
	if (!new_envp_cpy[j])
		(free_double_char(new_envp_cpy), exec_exit(shell, NULL, EC_MALLOC_E));
	free_double_char(shell->envp_cpy);
	shell->envp_cpy = new_envp_cpy;
}

void	exec_export(t_shell *shell, t_arg *cur_cmd, int fd)
{
	int	i;
	int	var_index;

	shell->exit_status = 0;
	if (cur_cmd->arg_lst[1] == NULL)
		return (exec_env(shell, 1, fd));
	i = 1;
	while (cur_cmd->arg_lst[i])
	{
		if (is_id_valid(cur_cmd->arg_lst[i], shell) == SUCCESS
			&& is_c(cur_cmd->arg_lst[i], '=', 1) == SUCCESS)
		{
			var_index = get_var_index(shell, cur_cmd->arg_lst[i], '=');
			if (var_index == -2)
				exec_exit(shell, NULL, EC_MALLOC_E);
			else if (var_index >= 0)
				update_var(shell, cur_cmd, var_index, i);
			else
				add_var(shell, cur_cmd, i);
		}
		i++;
	}
}
