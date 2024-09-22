/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkassel <rkassel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 19:02:12 by rgrochow          #+#    #+#             */
/*   Updated: 2024/09/16 16:43:46 by rkassel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	remove_var(t_shell *shell, int var_index)
{
	char	**new_envp_cpy;
	int		envp_len;
	int		i;
	int		j;

	envp_len = get_envp_len(shell->envp_cpy);
	new_envp_cpy = (char **)ft_calloc(sizeof(char *), envp_len);
	if (!new_envp_cpy)
		exec_exit(shell, NULL, EC_MALLOC_E);
	i = 0;
	j = 0;
	while (shell->envp_cpy[i])
	{
		if (i != var_index)
		{
			new_envp_cpy[j] = ft_strdup(shell->envp_cpy[i]);
			if (!new_envp_cpy[j])
				(free_double_char(new_envp_cpy),
					exec_exit(shell, NULL, EC_MALLOC_E));
			j++;
		}
		i++;
	}
	(free_double_char(shell->envp_cpy), shell->envp_cpy = new_envp_cpy);
}

void	exec_unset(t_shell *shell, t_arg *cur_cmd)
{
	int	i;
	int	var_index;

	shell->exit_status = 0;
	if (cur_cmd->arg_lst[1] == NULL)
		return ;
	i = 1;
	while (cur_cmd->arg_lst[i])
	{
		if (is_c(cur_cmd->arg_lst[i], '=', 1) == FAILURE)
		{
			var_index = get_var_index(shell, cur_cmd->arg_lst[i], '=');
			if (var_index == -2)
				exec_exit(shell, NULL, EC_MALLOC_E);
			else if (var_index >= 0)
				remove_var(shell, var_index);
		}
		i++;
	}
}
