/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkassel <rkassel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 16:06:41 by rgrochow          #+#    #+#             */
/*   Updated: 2024/09/11 12:03:17 by rkassel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_n_flag(char *arg_lst_i)
{
	int	j;

	if (arg_lst_i[0] != '-')
		return (FAILURE);
	j = 1;
	while (arg_lst_i[j])
	{
		if (arg_lst_i[j] != 'n')
			return (FAILURE);
		j++;
	}
	return (SUCCESS);
}

void	print_without_extra_spaces(char *next_value, int fd)
{
	int	first_word_met;
	int	i;

	first_word_met = 0;
	i = 0;
	while (next_value[i])
	{
		if (is_whitespace(next_value[i]))
		{
			if (next_value[i + 1] && !is_whitespace(next_value[i + 1])
				&& first_word_met == 1)
				ft_putchar_fd(' ', fd);
			i++;
		}
		else
		{
			first_word_met = 1;
			ft_putchar_fd(next_value[i++], fd);
		}
	}
}

int	handle_print(t_arg *next, int fd)
{
	if (next->dollar_status_arg == HANDLED)
		print_without_extra_spaces(next->value, fd);
	else
		ft_putstr_fd(next->value, fd);
	if (next->next && ft_strcmp(next->next->value, "|") != 0)
		ft_putchar_fd(' ', fd);
	return (1);
}

void	exec_echo(t_shell *shell, t_arg *cur_cmd, int fd)
{
	t_arg	*next;
	int		nl;
	int		ignore_n_flag;

	next = cur_cmd->next;
	nl = 1;
	ignore_n_flag = 0;
	if (next)
	{
		while (next && ft_strcmp(next->value, "|") != 0
			&& (ft_strcmp(next->type, "cmd_arg_flag") == 0
				|| ft_strcmp(next->type, "cmd_arg_fd") == 0))
		{
			if (!is_n_flag(next->value) && ignore_n_flag == 0)
				nl = 0;
			else
				ignore_n_flag = handle_print(next, fd);
			next = next->next;
		}
	}
	if (nl)
		ft_putchar_fd('\n', fd);
	shell->exit_status = 0;
}
