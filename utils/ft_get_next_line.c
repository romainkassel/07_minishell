/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_next_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: debian <debian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 14:52:22 by rkassel           #+#    #+#             */
/*   Updated: 2024/08/15 12:13:20 by debian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_residu(char *buff, char *residu)
{
	int	i;
	int	j;

	if (!buff)
		return (NULL);
	i = 0;
	while (buff[i])
	{
		if (buff[i] == '\n')
			break ;
		i++;
	}
	if ((int)buff[i] == 0 || (buff[i] == '\n' && (int)buff[i + 1] == 0))
	{
		if (residu)
			free(residu);
		return (NULL);
	}
	(free(residu), residu = ft_calloc(1, ft_strlen(buff) - i));
	if (!residu)
		return (NULL);
	j = 0;
	while (buff[++i])
		residu[j++] = buff[i];
	return (residu[j] = '\0', residu);
}

char	*get_line_to_return(char *global_buff)
{
	char	*line_to_return;
	int		i;

	if (!global_buff)
		return (NULL);
	i = -1;
	while (global_buff[++i])
		if (global_buff[i] == '\n')
			break ;
	line_to_return = (char *)ft_calloc(sizeof(char), ++i + 2);
	if (!line_to_return)
		return (NULL);
	i = -1;
	while (global_buff[++i])
	{
		line_to_return[i] = global_buff[i];
		if (global_buff[i] == '\n')
			return (line_to_return[++i] = '\0', line_to_return);
	}
	return (line_to_return[++i] = '\0', line_to_return);
}

char	*strcat_global_buff(char *global_buff, char *tmp_buff, int read_bytes)
{
	char	*tmp;
	int		len;

	if (!global_buff && !tmp_buff)
		return (NULL);
	len = 0;
	if (global_buff)
		len += ft_strlen(global_buff);
	if (tmp_buff && read_bytes == -1)
		len += ft_strlen(tmp_buff);
	if (tmp_buff && read_bytes)
		len += read_bytes;
	tmp = (char *)ft_calloc(sizeof(char), len + 2);
	if (!tmp)
		return (NULL);
	if (global_buff)
		(ft_strcat_gnl(tmp, global_buff, -1), free(global_buff));
	if (tmp_buff)
		ft_strcat_gnl(tmp, tmp_buff, read_bytes);
	return (tmp);
}

char	*get_global_buff(int fd)
{
	char	*global_buff;
	int		read_bytes;
	char	*tmp_buff;

	global_buff = NULL;
	tmp_buff = (char *)ft_calloc(sizeof(char), BUFFER_SIZE);
	if (!tmp_buff)
		return (NULL);
	read_bytes = read(fd, tmp_buff, BUFFER_SIZE);
	if (read_bytes <= 0)
		return (free(tmp_buff), NULL);
	global_buff = strcat_global_buff(global_buff, tmp_buff, read_bytes);
	while (read_bytes == BUFFER_SIZE)
	{
		read_bytes = read(fd, tmp_buff, BUFFER_SIZE);
		global_buff = strcat_global_buff(global_buff, tmp_buff, read_bytes);
	}
	free(tmp_buff);
	return (global_buff);
}

char	*ft_get_next_line(int fd)
{
	char		*global_buff;
	char		*line_to_return;
	static char	*residu[1024];

	if (BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0 || fd < 0)
	{
		if (residu[fd])
			(free(residu[fd]), residu[fd] = NULL);
		return (NULL);
	}
	global_buff = NULL;
	if (!residu[fd])
		global_buff = get_global_buff(fd);
	else
		global_buff = strcat_global_buff(global_buff, residu[fd], -1);
	line_to_return = get_line_to_return(global_buff);
	residu[fd] = get_residu(global_buff, residu[fd]);
	return (free(global_buff), line_to_return);
}
