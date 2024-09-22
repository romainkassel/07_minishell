/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: debian <debian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 21:48:22 by rgrochow          #+#    #+#             */
/*   Updated: 2024/09/15 08:38:24 by debian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_arg(const char *ptr, int s_quote, int d_quote)
{
	if (*ptr && ((s_quote % 2 == 0
				&& d_quote % 2 == 0 && !is_whitespace(*ptr))
			|| (s_quote % 2 == 1)
			|| (d_quote % 2 == 1)))
	{
		return (SUCCESS);
	}
	else
		return (FAILURE);
}

void	count_args(const char *ptr, t_shell *shell, int s_quote, int d_quote)
{
	while (*ptr)
	{
		s_quote = 0;
		d_quote = 0;
		while (*ptr && is_whitespace(*ptr))
			ptr++;
		if (*ptr)
		{
			shell->argc++;
			while (!is_arg(ptr, s_quote, d_quote))
			{
				if (*ptr == '\'' && d_quote == 0)
					s_quote++;
				else if (*ptr == '"' && s_quote == 0)
					d_quote++;
				ptr++;
			}
		}
	}
}

void	copy_args(const char *ptr, t_shell *shell, int s_quote, int d_quote)
{
	char		*start;
	int			i;

	i = 0;
	while (*ptr)
	{
		s_quote = 0;
		d_quote = 0;
		while (*ptr && is_whitespace(*ptr))
			ptr++;
		if (*ptr)
		{
			start = (char *)ptr;
			while (!is_arg(ptr, s_quote, d_quote))
			{
				if (*ptr == '\'' && d_quote == 0)
					s_quote++;
				else if (*ptr == '"' && s_quote == 0)
					d_quote++;
				ptr++;
			}
			shell->argv[i++] = ft_strndup(start, ptr - start, shell);
		}
	}
}

void	init_argv(t_shell *shell)
{
	shell->argv = (char **)ft_calloc(sizeof(char *), (shell->argc + 1));
	if (!shell->argv)
		exec_exit(shell, NULL, EC_MALLOC_E);
}

void	store_input(t_shell *shell, char *input)
{
	char		*input_copy;
	const char	*ptr;
	int			s_quote;
	int			d_quote;

	input_copy = ft_strdup(input);
	if (!input_copy)
		exec_exit(shell, NULL, EC_MALLOC_E);
	ptr = input_copy;
	s_quote = 0;
	d_quote = 0;
	count_args(ptr, shell, s_quote, d_quote);
	init_argv(shell);
	copy_args(ptr, shell, s_quote, d_quote);
	free(input_copy);
}
