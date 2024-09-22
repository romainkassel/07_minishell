/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_double_char.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkassel <rkassel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 12:38:16 by rgrochow          #+#    #+#             */
/*   Updated: 2024/08/09 18:16:45 by rkassel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_print_double_char(char **tab, char *lines_name)
{
	int	i;

	i = 0;
	if (tab)
	{
		while (tab[i])
		{
			printf("%s[i] : %s\n", lines_name, tab[i]);
			i++;
		}
	}
}
