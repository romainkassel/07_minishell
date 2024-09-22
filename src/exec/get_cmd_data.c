/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd_data.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkassel <rkassel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 22:13:18 by rgrochow          #+#    #+#             */
/*   Updated: 2024/09/16 12:36:19 by rkassel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_arg_count(t_arg *current)
{
	int		arg_count;

	current = current->next;
	arg_count = 0;
	while (current && ft_strcmp(current->value, "|") != 0)
	{
		if (ft_strcmp(current->type, "cmd_arg_flag") == 0
			|| ft_strcmp(current->type, "cmd_arg_fd") == 0)
		{
			arg_count++;
		}
		current = current->next;
	}
	return (arg_count);
}

void	get_arg_lst(t_arg *current, t_shell *shell)
{
	t_arg	*next;
	int		i;

	current->arg_lst[0] = ft_strdup(current->value);
	if (!current->arg_lst[0])
		exec_exit(shell, NULL, EC_MALLOC_E);
	i = 1;
	next = current->next;
	while (next && ft_strcmp(next->value, "|") != 0)
	{
		if (ft_strcmp(next->type, "cmd_arg_flag") == 0
			|| ft_strcmp(next->type, "cmd_arg_fd") == 0)
		{
			current->arg_lst[i] = ft_strdup(next->value);
			if (!current->arg_lst[i])
				exec_exit(shell, NULL, EC_MALLOC_E);
			i++;
		}
		next = next->next;
	}
}

void	get_cmd_path(t_arg *cur, t_shell *shell)
{
	int		i;

	if (access(cur->value, X_OK) == 0 && !is_c(cur->value, '/', 0))
	{
		cur->cmd_path = ft_strdup(cur->value);
		if (!cur->cmd_path)
			exec_exit(shell, NULL, EC_MALLOC_E);
		return ;
	}
	if (!shell->envp_paths || ft_strcmp(cur->value, "") == 0)
		return ;
	i = -1;
	while (shell->envp_paths[++i])
	{
		cur->cmd_path = ft_strjoin(shell->envp_paths[i], 0, cur->value, 0);
		if (!cur->cmd_path)
			exec_exit(shell, NULL, EC_MALLOC_E);
		if (access(cur->cmd_path, X_OK) == 0)
			return ;
		else
		{
			free(cur->cmd_path);
			cur->cmd_path = NULL;
		}
	}
}

void	get_builtin_flag(t_arg *current)
{
	if (ft_strcmp(current->value, "echo") == 0
		|| ft_strcmp(current->value, "cd") == 0
		|| ft_strcmp(current->value, "pwd") == 0
		|| ft_strcmp(current->value, "export") == 0
		|| ft_strcmp(current->value, "unset") == 0
		|| ft_strcmp(current->value, "env") == 0
		|| ft_strcmp(current->value, "exit") == 0)
	{
		current->is_builtin = 1;
	}
}

void	get_cmd_data(t_shell *shell)
{
	int		i;
	int		arg_count;
	t_arg	*cur;

	cur = shell->arg;
	i = 0;
	while (cur)
	{
		if (ft_strcmp(cur->type, "cmd") == 0)
		{
			arg_count = get_arg_count(cur);
			cur->arg_lst = (char **)ft_calloc(sizeof(char *), arg_count + 2);
			if (!cur->arg_lst)
				exec_exit(shell, NULL, EC_MALLOC_E);
			get_builtin_flag(cur);
			get_arg_lst(cur, shell);
			get_cmd_path(cur, shell);
			i++;
		}
		cur = cur->next;
	}
}
