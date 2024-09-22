/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_envp_cpy.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: debian <debian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 08:54:46 by debian            #+#    #+#             */
/*   Updated: 2024/08/16 09:03:54 by debian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_envp_len(char **envp)
{
	int	envp_len;

	envp_len = 0;
	while (envp[envp_len])
		envp_len++;
	return (envp_len);
}

void	get_envp_cpy(t_shell *shell, char **envp)
{
	int	envp_len;
	int	i;

	if (!envp)
	{
		shell->envp_cpy = NULL;
		return ;
	}
	envp_len = get_envp_len(envp);
	shell->envp_cpy = (char **)ft_calloc(sizeof(char *), (envp_len + 1));
	if (!shell->envp_cpy)
		exec_exit(shell, NULL, EC_MALLOC_E);
	i = 0;
	while (envp[i])
	{
		shell->envp_cpy[i] = ft_strdup(envp[i]);
		if (!shell->envp_cpy[i])
			exec_exit(shell, NULL, EC_MALLOC_E);
		i++;
	}
	shell->envp_cpy[i] = NULL;
}
