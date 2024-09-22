/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: debian <debian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 16:21:28 by rgrochow          #+#    #+#             */
/*   Updated: 2024/08/19 02:12:20 by debian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strjoin(char *s1, int free_s1, char *s2, int free_s2)
{
	char	*str;
	int		i;
	int		j;

	str = (char *)ft_calloc(sizeof(char), (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!str)
		return (NULL);
	i = 0;
	j = 0;
	if (s1)
	{
		while (s1[i])
			str[i++] = s1[j++];
		if (free_s1 == 1)
			free(s1);
	}
	j = 0;
	if (s2)
	{
		while (s2[j])
			str[i++] = s2[j++];
		if (free_s2 == 1)
			free(s2);
	}
	return (str);
}
