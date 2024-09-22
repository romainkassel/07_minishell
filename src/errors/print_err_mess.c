/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_err_mess.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkassel <rkassel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 04:08:34 by debian            #+#    #+#             */
/*   Updated: 2024/09/07 12:21:44 by rkassel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_s_to_print(char *s_to_print, t_shell *shell)
{
	int	s_to_print_len;

	s_to_print = ft_strjoin(s_to_print, 1, "\n", 0);
	if (!s_to_print)
		(free(s_to_print), exec_exit(shell, NULL, EC_MALLOC_E));
	s_to_print_len = ft_strlen(s_to_print);
	write(2, s_to_print, s_to_print_len);
	free(s_to_print);
}

void	print_err_mess(char *s1, char *s2, char *s3, t_shell *shell)
{
	char	*s_to_print;

	s_to_print = NULL;
	if (s1)
	{
		s_to_print = ft_strjoin(E_BASH, 0, s1, 0);
		if (!s_to_print)
			exec_exit(shell, NULL, EC_MALLOC_E);
	}
	if (s2)
	{
		s_to_print = ft_strjoin(s_to_print, 1, s2, 0);
		if (!s_to_print)
			(free(s_to_print), exec_exit(shell, NULL, EC_MALLOC_E));
	}
	if (s3)
	{
		s_to_print = ft_strjoin(s_to_print, 1, s3, 0);
		if (!s_to_print)
			(free(s_to_print), exec_exit(shell, NULL, EC_MALLOC_E));
	}
	if (s_to_print)
		print_s_to_print(s_to_print, shell);
}

void	print_err_mess_cd(char *s1, char *s2, char *s3, t_shell *shell)
{
	char	*s_to_print;

	s_to_print = NULL;
	if (s1)
	{
		s_to_print = ft_strjoin(E_BASH_CD, 0, s1, 0);
		if (!s_to_print)
			exec_exit(shell, NULL, EC_MALLOC_E);
	}
	if (s2)
	{
		s_to_print = ft_strjoin(s_to_print, 1, s2, 0);
		if (!s_to_print)
			(free(s_to_print), exec_exit(shell, NULL, EC_MALLOC_E));
	}
	if (s3)
	{
		s_to_print = ft_strjoin(s_to_print, 1, s3, 0);
		if (!s_to_print)
			(free(s_to_print), exec_exit(shell, NULL, EC_MALLOC_E));
	}
	if (s_to_print)
		print_s_to_print(s_to_print, shell);
}
