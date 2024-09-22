/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: debian <debian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 12:38:16 by rgrochow          #+#    #+#             */
/*   Updated: 2024/09/15 08:39:32 by debian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strndup(char *s, size_t n, t_shell *shell)
{
	char	*new_str;
	size_t	len;
	size_t	i;
	size_t	j;
	size_t	f;

	f = 0;
	len = 0;
	while (len < n && s[len] != '\0')
		len++;
	new_str = malloc(len + 1 + f);
	if (!new_str)
		exec_exit(shell, NULL, EC_MALLOC_E);
	i = 0;
	j = 0;
	while (i < len + f)
	{
		new_str[i] = s[j];
		i++;
		j++;
	}
	new_str[len + f] = '\0';
	return (new_str);
}
