/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_var_index.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkassel <rkassel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 19:01:41 by rgrochow          #+#    #+#             */
/*   Updated: 2024/09/11 17:15:08 by rkassel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_var_name_len(char *s, char c)
{
	int	i;

	if (s[0] == '?' && s[-1] && s[-1] == '$')
		return (1);
	i = 0;
	while (s[i] && s[i] != c && !is_whitespace(s[i])
		&& s[i] != '\'' && s[i] != '"' && s[i] != '=' && s[i] != '|')
		i++;
	return (i);
}

char	*get_var_name(char *s, char c)
{
	char	*var_name;
	int		var_name_len;
	int		i;

	var_name_len = get_var_name_len(s, c);
	var_name = (char *)ft_calloc(sizeof(char), (var_name_len + 1));
	if (!var_name)
		return (NULL);
	i = 0;
	while (i < var_name_len)
	{
		var_name[i] = s[i];
		i++;
	}
	return (var_name);
}

int	get_var_index(t_shell *shell, char *s, char c)
{
	int		i;
	char	*s_var_name;
	char	*env_var_name;

	s_var_name = get_var_name(s, c);
	if (!s_var_name)
		return (-2);
	i = 0;
	while (shell->envp_cpy[i])
	{
		env_var_name = get_var_name(shell->envp_cpy[i], '=');
		if (!env_var_name)
			return (free(s_var_name), -2);
		if (ft_strcmp(s_var_name, env_var_name) == 0)
			return (free(s_var_name), free(env_var_name), i);
		else
			(free(env_var_name), i++);
	}
	return (free(s_var_name), -1);
}
