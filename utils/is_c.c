/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_c.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkassel <rkassel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 16:21:28 by rgrochow          #+#    #+#             */
/*   Updated: 2024/09/10 13:38:17 by rkassel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_c(char *s, char c, int start_i)
{
	if (s)
	{
		while (s[start_i])
		{
			if (s[start_i] == c)
				return (SUCCESS);
			start_i++;
		}
	}
	return (FAILURE);
}
