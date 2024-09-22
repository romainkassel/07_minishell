/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_env_var.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkassel <rkassel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 21:48:22 by rgrochow          #+#    #+#             */
/*   Updated: 2024/09/16 16:42:29 by rkassel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_var_value(char *argv_i, char *exp_argv_i, t_shell *shell)
{
	int		var_index;
	int		var_len;
	int		var_name_len;
	char	*var_value;
	int		k;

	var_index = get_var_index(shell, argv_i, '$');
	if (var_index == -2)
		(free(exp_argv_i), exec_exit(shell, NULL, EC_MALLOC_E));
	else if (var_index >= 0)
	{
		var_len = ft_strlen(shell->envp_cpy[var_index]);
		var_name_len = get_var_name_len(shell->envp_cpy[var_index], '=');
		var_value = (char *)ft_calloc(sizeof(char), (var_len - var_name_len));
		if (!var_value)
			(free(exp_argv_i), exec_exit(shell, NULL, EC_MALLOC_E));
		k = 0;
		var_name_len++;
		while (shell->envp_cpy[var_index][var_name_len])
			var_value[k++] = shell->envp_cpy[var_index][var_name_len++];
		return (var_value);
	}
	return (NULL);
}

char	*get_exp_argv_i_dol(char *argv_i, char *exp_argv_i, t_shell *shell)
{
	char	*var_value;

	if (argv_i[0] == '?')
		var_value = get_exit_code(shell);
	else
		var_value = get_var_value(argv_i, exp_argv_i, shell);
	exp_argv_i = ft_strjoin(exp_argv_i, 1, var_value, 1);
	if (!exp_argv_i)
	{
		free(exp_argv_i);
		free(var_value);
		exec_exit(shell, NULL, EC_MALLOC_E);
	}
	return (exp_argv_i);
}

char	*get_exp_argv_i_c(char *exp_argv_i, char c, t_shell *shell)
{
	char	argv_i_j[2];

	argv_i_j[0] = c;
	argv_i_j[1] = '\0';
	exp_argv_i = ft_strjoin(exp_argv_i, 1, argv_i_j, 0);
	if (!exp_argv_i)
		(free(exp_argv_i), exec_exit(shell, NULL, EC_MALLOC_E));
	return (exp_argv_i);
}

char	*init_exp_argv_i(t_shell *shell)
{
	char	*exp_argv_i;

	exp_argv_i = (char *)ft_calloc(sizeof(char), 1);
	if (!exp_argv_i)
		exec_exit(shell, NULL, EC_MALLOC_E);
	return (exp_argv_i);
}

char	*handle_env_var(char *argv_i, t_shell *shell)
{
	char	*exp_argv_i;
	int		j;
	int		s_quote;
	int		d_quote;

	exp_argv_i = init_exp_argv_i(shell);
	s_quote = 0;
	d_quote = 0;
	j = 0;
	while (argv_i[j])
	{
		if (incr_s_quote_flag(argv_i, j, d_quote, s_quote) == SUCCESS)
			s_quote++;
		else if (incr_d_quote_flag(argv_i, j, d_quote, s_quote) == SUCCESS)
			d_quote++;
		if (should_dollar_be_exp(argv_i, j, s_quote) == SUCCESS)
		{
			exp_argv_i = get_exp_argv_i_dol(argv_i + j + 1, exp_argv_i, shell);
			j += get_var_name_len(argv_i + j + 1, '$');
		}
		else
			exp_argv_i = get_exp_argv_i_c(exp_argv_i, argv_i[j], shell);
		j++;
	}
	return (update_dollar_flag(exp_argv_i, shell), free(argv_i), exp_argv_i);
}
