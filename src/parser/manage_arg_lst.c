/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_arg_lst.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: debian <debian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 21:48:22 by rgrochow          #+#    #+#             */
/*   Updated: 2024/09/15 08:38:15 by debian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_arg_lst(t_arg *arg)
{
	t_arg	*tmp;

	if (arg)
	{
		tmp = arg;
		while (tmp)
		{
			tmp = arg->next;
			if (arg->value)
				(free(arg->value), arg->value = NULL);
			if (arg->arg_lst)
				free_double_char(arg->arg_lst);
			if (arg->cmd_path)
				(free(arg->cmd_path), arg->cmd_path = NULL);
			free(arg);
			arg = tmp;
		}
	}
}

char	*get_arg_value(char *arg, t_shell *shell)
{
	char	*arg_value;

	arg_value = ft_strdup(arg);
	if (!arg_value)
		exec_exit(shell, NULL, EC_MALLOC_E);
	return (arg_value);
}

t_arg	*ft_lstnew(t_shell *shell, char *arg)
{
	t_arg	*new_node;

	new_node = (t_arg *)ft_calloc(sizeof(t_arg), 1);
	if (!new_node)
		exec_exit(shell, NULL, EC_MALLOC_E);
	new_node->index = -1;
	new_node->type[0] = '\0';
	new_node->value = get_arg_value(arg, shell);
	new_node->pipe_scope = -1;
	new_node->pipe_nb = -1;
	new_node->is_builtin = 0;
	get_dollar_and_quote_status(new_node, shell);
	new_node->arg_lst = NULL;
	new_node->cmd_path = NULL;
	new_node->here_doc = NULL;
	new_node->next = NULL;
	new_node->prev = NULL;
	return (new_node);
}

void	ft_lstadd_next(t_arg *cur, t_arg *new, t_arg *next)
{
	if (!cur || !new)
		return ;
	new->prev = cur;
	cur->next = new;
	new->next = next;
	if (next)
		next->prev = new;
}

void	init_arg_with_value(t_shell *shell)
{
	t_arg	*cur;
	t_arg	*new_node;
	int		i;

	i = -1;
	while (++i < shell->argc)
	{
		if (is_c(shell->argv[i], '$', 0) == SUCCESS)
			shell->argv[i] = handle_env_var(shell->argv[i], shell);
		if (!is_c(shell->argv[i], '\'', 0) || !is_c(shell->argv[i], '"', 0))
			shell->argv[i] = handle_quotes(shell->argv[i], shell);
		if (shell->dollar_status_shell != HANDLED_BUT_EMPTY)
		{
			new_node = ft_lstnew(shell, shell->argv[i]);
			if (i == 0 || !shell->arg)
			{
				shell->arg = new_node;
				cur = shell->arg;
			}
			else
				(ft_lstadd_next(cur, new_node, NULL), cur = cur->next);
		}
		shell->dollar_status_shell = NO_HANDLED;
		shell->quote_status_shell = NO_HANDLED;
	}
}
