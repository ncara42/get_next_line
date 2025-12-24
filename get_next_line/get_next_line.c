/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncaravac <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 02:06:10 by ncaravac          #+#    #+#             */
/*   Updated: 2025/12/23 13:15:31 by ncaravac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_line(int bytes, char **stash, char *line)
{
	int		end;
	char	*tmp;

	tmp = NULL;
	end = 0;
	if (bytes < 0 || *stash == NULL || (*stash)[end] == '\0')
		return (NULL);
	while ((*stash)[end] != '\n' && (*stash)[end])
		end++;
	if ((*stash)[end] == '\n')
	{
		line = ft_substr(*stash, 0, end + 1);
		tmp = ft_strdup(*stash + end + 1);
		free(*stash);
		*stash = tmp;
	}
	else
	{
		line = ft_strdup(*stash);
		free(*stash);
		*stash = NULL;
	}
	return (line);
}

int	get_buffer(char **stash, char *buffer, int fd)
{
	int		bytes;
	char	*tmp;

	tmp = NULL;
	bytes = read(fd, buffer, BUFFER_SIZE);
	while (bytes > 0)
	{
		buffer[bytes] = '\0';
		if (!*stash)
			*stash = ft_strdup(buffer);
		else
		{
			tmp = ft_strjoin(*stash, buffer);
			free(*stash);
			*stash = tmp;
		}
		if (ft_strchr(buffer, '\n'))
			break ;
		bytes = read(fd, buffer, BUFFER_SIZE);
	}
	free(buffer);
	return (bytes);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*buffer;
	char		*line;
	int			bytes;

	if (BUFFER_SIZE <= 0)
		return (NULL);
	line = NULL;
	buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	bytes = get_buffer(&stash, buffer, fd);
	line = get_line(bytes, &stash, line);
	return (line);
}
