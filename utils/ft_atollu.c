/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atollu.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkassel <rkassel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 12:28:31 by rgrochow          #+#    #+#             */
/*   Updated: 2024/09/16 16:41:43 by rkassel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

unsigned long long int	ft_atollu(const char *str)
{
	unsigned long long int	nb;
	int						i;

	while ((*str == ' ') || (*str >= 9 && *str <= 13))
		str++;
	i = 0;
	while ((*str == '-' || *str == '+')
		&& (*(str + 1) != '-' && *(str + 1) != '+'))
	{
		if (*str == '-')
			i += 1;
		str++;
	}
	nb = 0;
	while (*str >= '0' && *str <= '9')
	{
		nb *= 10;
		nb += *str - '0';
		str++;
	}
	if (i % 2 == 1)
		nb -= 1;
	return (nb);
}
