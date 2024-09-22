/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_prompt.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgrochow <staafnet@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 23:16:53 by rgrochow          #+#    #+#             */
/*   Updated: 2024/09/05 21:18:03 by rgrochow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*read_file(const char *filepath, char *buffer, size_t size)
{
	int		fd;
	ssize_t	bytes_read;

	fd = open(filepath, O_RDONLY);
	if (fd == -1)
		return (NULL);
	bytes_read = read(fd, buffer, size - 1);
	if (bytes_read == -1)
		return (close(fd), NULL);
	buffer[bytes_read - 1] = '\0';
	close(fd);
	return (buffer);
}

static char	*get_username(void)
{
	char	*username;

	username = getenv("USER");
	if (!username)
		username = "user";
	return (username);
}

static char	*get_hostname(void)
{
	static char	hostname[128];

	if (!read_file("/etc/hostname", hostname, sizeof(hostname)))
		ft_strcpy(hostname, "host");
	return (hostname);
}

static char	*get_path(void)
{
	static char	path[1024];
	char		cwd[1024];
	char		*home;
	char		tmp[1024];

	if (!getcwd(cwd, sizeof(cwd)))
		ft_strcpy(cwd, "path");
	home = getenv("HOME");
	if (home && strstr(cwd, home) == cwd)
	{
		ft_strcpy(tmp, "~");
		ft_strcat(tmp, cwd + ft_strlen(home));
		ft_strcpy(cwd, tmp);
	}
	strcpy(path, cwd);
	return (path);
}

char	*build_prompt(void)
{
	char	*prompt;

	prompt = malloc(ft_strlen(get_username())
			+ ft_strlen(get_hostname()) + ft_strlen(get_path()) + 5);
	if (!prompt)
		return (NULL);
	ft_strcpy(prompt, get_username());
	ft_strcat(prompt, "@");
	ft_strcat(prompt, get_hostname());
	ft_strcat(prompt, ":");
	ft_strcat(prompt, get_path());
	ft_strcat(prompt, "$ ");
	return (prompt);
}
