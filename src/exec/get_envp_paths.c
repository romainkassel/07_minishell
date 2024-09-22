/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_envp_paths.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: debian <debian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 22:13:18 by rgrochow          #+#    #+#             */
/*   Updated: 2024/09/15 08:36:52 by debian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_last_slash(char **env_paths, t_shell *shell)
{
	int		i;

	i = 0;
	while (env_paths[i])
	{
		env_paths[i] = ft_strjoin(env_paths[i], 1, "/", 0);
		if (!env_paths[i])
			exec_exit(shell, NULL, EC_MALLOC_E);
		i++;
	}
}

char	*del_path_word(char *env_paths_0, t_shell *shell)
{
	char	*new_str;

	new_str = ft_strdup(env_paths_0 + 5);
	if (!new_str)
		exec_exit(shell, NULL, EC_MALLOC_E);
	free(env_paths_0);
	return (new_str);
}

void	get_envp_paths(t_shell *shell)
{
	int			i;

	if (!shell->envp_cpy)
		return ;
	i = 0;
	while (shell->envp_cpy[i])
	{
		if (shell->envp_cpy[i][0] == 'P' && shell->envp_cpy[i][1] == 'A'
			&& shell->envp_cpy[i][2] == 'T' && shell->envp_cpy[i][3] == 'H'
			&& shell->envp_cpy[i][4] == '=')
		{
			shell->envp_paths = ft_split(shell->envp_cpy[i], ':');
			if (!shell->envp_paths)
				exec_exit(shell, NULL, EC_MALLOC_E);
		}
		i++;
	}
	if (shell->envp_paths)
	{
		shell->envp_paths[0] = del_path_word(shell->envp_paths[0], shell);
		add_last_slash(shell->envp_paths, shell);
	}
}
