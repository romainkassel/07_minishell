/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkassel <rkassel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 12:38:16 by rgrochow          #+#    #+#             */
/*   Updated: 2024/09/11 16:49:48 by rkassel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	save_one_line(char s, char c, int j, int i)
{
	if (s == c)
	{
		j = i;
		return (j);
	}
	else
		return (j);
}

static char	**count_words(char const *s, char c)
{
	char	**arr;
	int		count;
	int		i;

	count = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == 0))
		{
			count++;
			i++;
		}
		else
			i++;
	}
	arr = (char **)ft_calloc(sizeof(char *), (count + 1));
	if (!arr)
		return (NULL);
	return (arr);
}

static char	*fill_word(char const *s, int j, int i)
{
	char	*str;
	int		k;

	str = (char *)ft_calloc(sizeof(char), (i - j + 2));
	if (!str)
		return (NULL);
	else
	{
		k = 0;
		while (j != i)
		{
			str[k] = s[j];
			k++;
			j++;
		}
		str[k++] = s[j];
		str[k] = '\0';
		return (str);
	}
}

static void	*free_arr(char **arr, int k)
{
	int	i;

	i = 0;
	while (k)
	{
		free(arr[i]);
		i++;
		k--;
	}
	free(arr);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char	**arr;
	int		i;
	int		j;
	int		k;

	arr = count_words(s, c);
	if (!arr)
		return (NULL);
	i = -1;
	j = 0;
	k = 0;
	while (s[++i])
	{
		if (s[i] != c && ((i > 0 && s[i - 1] == c) || i == 0)
			&& (s[i + 1] != c && s[i + 1] != 0))
			j = i;
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == 0))
		{
			j = save_one_line(s[i - 1], c, j, i);
			arr[k++] = fill_word(s, j, i);
			if (!arr[k - 1])
				return (free_arr(arr, k - 1));
		}
	}
	return (arr);
}
