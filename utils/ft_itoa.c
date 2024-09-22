/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcpy copy.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: debian <debian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 22:51:59 by rgrochow          #+#    #+#             */
/*   Updated: 2024/08/23 09:06:26 by debian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_get_count(long int nb)
{
	int	count;

	count = 1;
	if (nb < 0)
	{
		count++;
		nb *= -1;
	}
	while (nb / 10)
	{
		count++;
		nb /= 10;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	char		*str;
	long int	nb;
	int			count;

	nb = n;
	count = ft_get_count(nb);
	str = (char *)malloc(sizeof(char) * count + 1);
	if (!str)
		return (NULL);
	if (nb < 0)
	{
		str[0] = '-';
		nb *= -1;
	}
	str[count--] = '\0';
	while (nb / 10)
	{
		str[count--] = nb % 10 + 48;
		nb /= 10;
	}
	str[count--] = nb + 48;
	return (str);
}
