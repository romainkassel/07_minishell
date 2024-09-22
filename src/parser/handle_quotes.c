/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: debian <debian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 21:48:22 by rgrochow          #+#    #+#             */
/*   Updated: 2024/08/19 14:12:16 by debian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_quotes_count(char *argv_i)
{
	int		j;
	int		s_quote;
	int		d_quote;

	s_quote = 0;
	d_quote = 0;
	j = 0;
	while (argv_i[j])
	{
		if (incr_s_quote_flag(argv_i, j, d_quote, s_quote) == SUCCESS)
			s_quote++;
		else if (incr_d_quote_flag(argv_i, j, d_quote, s_quote) == SUCCESS)
			d_quote++;
		j++;
	}
	return (s_quote + d_quote);
}

char	*get_unquo_argv_i(char *unquo_argv_i, char *argv_i)
{
	int	j;
	int	k;
	int	s_quote;
	int	d_quote;

	j = 0;
	k = 0;
	s_quote = 0;
	d_quote = 0;
	while (argv_i[j])
	{
		if (incr_s_quote_flag(argv_i, j, d_quote, s_quote) == SUCCESS)
			s_quote++;
		else if (incr_d_quote_flag(argv_i, j, d_quote, s_quote) == SUCCESS)
			d_quote++;
		else
		{
			unquo_argv_i[k] = argv_i[j];
			k++;
		}
		j++;
	}
	return (unquo_argv_i);
}

char	*handle_quotes(char *argv_i, t_shell *shell)
{
	char	*unquo_argv_i;
	int		quotes_count;
	int		new_len;

	quotes_count = get_quotes_count(argv_i);
	new_len = (ft_strlen(argv_i) - quotes_count) + 1;
	unquo_argv_i = (char *)ft_calloc(sizeof(char), (new_len + 1));
	if (!unquo_argv_i)
		exec_exit(shell, NULL, EC_MALLOC_E);
	unquo_argv_i = get_unquo_argv_i(unquo_argv_i, argv_i);
	if (ft_strcmp(argv_i, unquo_argv_i) != 0)
		shell->quote_status_shell = HANDLED;
	free(argv_i);
	return (unquo_argv_i);
}
