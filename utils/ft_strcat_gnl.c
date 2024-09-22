/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat_gnl.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: debian <debian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 22:54:01 by rgrochow          #+#    #+#             */
/*   Updated: 2024/08/15 12:12:35 by debian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strcat_gnl(char *dest, char *src, int read_bytes)
{
	int	i;
	int	j;

	i = 0;
	while (dest[i])
		i++;
	if (read_bytes == -1)
		read_bytes = ft_strlen(src);
	j = 0;
	while (read_bytes--)
		dest[i++] = src[j++];
	return (dest[i] = '\0', dest);
}
