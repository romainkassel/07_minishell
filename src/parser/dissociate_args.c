/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dissociate_args.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: debian <debian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 21:48:22 by rgrochow          #+#    #+#             */
/*   Updated: 2024/09/15 08:37:25 by debian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_new_node_value(t_shell *shell, char *current_value, int i, int nb)
{
	char	*new_value;
	int		new_value_len;
	int		start_index;

	if (i == 0)
	{
		new_value_len = ft_strlen(current_value) - nb;
		start_index = nb;
	}
	else
	{
		new_value_len = ft_strlen(current_value) - i;
		start_index = i;
	}
	new_value = (char *)ft_calloc(sizeof(char), (new_value_len + 1));
	if (!new_value)
		exec_exit(shell, NULL, EC_MALLOC_E);
	i = 0;
	while (current_value[start_index])
		new_value[i++] = current_value[start_index++];
	new_value[i] = '\0';
	return (new_value);
}

char	*update_cur_value(t_shell *shell, char *cur_value, int i, int nb)
{
	char	*new_value;
	int		new_value_len;
	int		end_index;

	if (i == 0)
	{
		new_value_len = nb;
		end_index = nb;
	}
	else
	{
		new_value_len = i;
		end_index = i;
	}
	new_value = (char *)ft_calloc(sizeof(char), (new_value_len + 1));
	if (!new_value)
		exec_exit(shell, NULL, EC_MALLOC_E);
	i = -1;
	while (++i < end_index)
		new_value[i] = cur_value[i];
	new_value[i] = '\0';
	free(cur_value);
	return (new_value);
}

int	is_double_symbol(t_arg *current, int i)
{
	if ((current->value[i] == '<' && current->value[i + 1] == '<')
		|| (current->value[i] == '>' && current->value[i + 1] == '>')
		|| (current->value[i] == '$' && current->value[i + 1] == '?'))
		return (0);
	return (1);
}

int	is_single_symbol(t_arg *current, int i)
{
	if ((current->value[i] == '<'
			&& (i > 0 && current->value[i - 1] != '<'))
		|| (current->value[i] == '<'
			&& (current->value[i + 1] && current->value[i + 1] != '<'))
		|| (current->value[i] == '>'
			&& (i > 0 && current->value[i - 1] != '>'))
		|| (current->value[i] == '>'
			&& (current->value[i + 1] && current->value[i + 1] != '>'))
		|| (current->value[i] == '|'))
		return (0);
	return (1);
}

int	add_new_node(t_shell *shell, t_arg *current, int i, int nb)
{
	char	*new_value;
	t_arg	*new_node;

	new_value = get_new_node_value(shell, current->value, i, nb);
	new_node = ft_lstnew(shell, new_value);
	free(new_value);
	ft_lstadd_next(current, new_node, current->next);
	current->value = update_cur_value(shell, current->value, i, nb);
	i = ft_strlen(current->value) - 1;
	return (i);
}
