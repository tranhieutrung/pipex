/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hitran <hitran@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 22:40:08 by hitran            #+#    #+#             */
/*   Updated: 2024/07/03 18:49:05 by hitran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mylib.h"

static char	*ft_next(char *data)
{
	int		i;
	int		j;
	char	*rest;

	i = 0;
	while (data[i] && (data[i] != '\n'))
		++i;
	if (!data[i])
	{
		free(data);
		return (NULL);
	}
	rest = malloc(sizeof(char) * (ft_strlen_gnl(data) - i + 1));
	if (!rest)
	{
		free(data);
		return (NULL);
	}
	++i;
	j = 0;
	while (data[i])
		rest[j++] = data[i++];
	rest[j] = '\0';
	free(data);
	return (rest);
}

static char	*ft_line(char *data)
{
	int		i;
	char	*line;

	i = 0;
	if (!data[i])
		return (NULL);
	while (data[i] && (data[i] != '\n'))
		i++;
	if (data[i] == '\n')
		i++;
	line = ft_substr_gnl(data, 0, i);
	if (!line)
		return (NULL);
	return (line);
}

static char	*ft_read(int fd, char *data)
{
	char	*buffer;
	int		bytes;

	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (ft_free_gnl(&data));
	bytes = 1;
	while ((data && !ft_strchr_gnl(data, '\n') && bytes > 0) || !data)
	{
		bytes = read(fd, buffer, BUFFER_SIZE);
		if (bytes == -1)
		{
			free(buffer);
			return (ft_free_gnl(&data));
		}
		if (!bytes)
			break ;
		buffer[bytes] = '\0';
		data = ft_strjoin_gnl(data, buffer);
	}
	free(buffer);
	return (data);
}

char	*get_next_line(int fd)
{
	static char	*data[OPEN_MAX];
	char		*line;

	if ((fd < 0) || (BUFFER_SIZE <= 0) || (fd > OPEN_MAX))
		return (NULL);
	data[fd] = ft_read(fd, data[fd]);
	if (!data[fd])
		return (NULL);
	line = ft_line(data[fd]);
	if (!line)
		return (ft_free_gnl(&data[fd]));
	data[fd] = ft_next(data[fd]);
	return (line);
}
