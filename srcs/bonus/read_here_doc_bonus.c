/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_here_doc_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hitran <hitran@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 12:56:32 by hitran            #+#    #+#             */
/*   Updated: 2024/08/05 23:38:13 by hitran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static char	*realloc_buffer(char *buffer, int new_size)
{
	char	*new_buffer;

	new_buffer = (char *)ft_calloc(new_size, sizeof(char));
	if (!new_buffer)
	{
		free(buffer);
		exit(1);
	}
	ft_memcpy(new_buffer, buffer, new_size / 2);
	free(buffer);
	return (new_buffer);
}

static char	*read_line_from_stdin(int *pipe_id, int index)
{
	int		byte;
	int		buffer_size;
	char	c;
	char	*line;

	buffer_size = 1024;
	line = (char *)ft_calloc(buffer_size, sizeof(char));
	if (!line)
		exit(1);
	while (1)
	{
		byte = read(0, &c, 1);
		if (byte == -1)
			handle_read_error(pipe_id);
		if (byte == 0 || c == '\n')
			break ;
		line[index++] = c;
		if (index >= buffer_size)
		{
			buffer_size *= 2;
			line = realloc_buffer(line, buffer_size);
		}
	}
	line[index] = '\0';
	return (line);
}

void	read_here_doc(t_pipex *pipex, int *pipe_id)
{
	char	*line;

	while (1)
	{
		line = read_line_from_stdin(pipe_id, 0);
		if (ft_strcmp(line, pipex->argv[2]) == 0)
		{
			free(line);
			break ;
		}
		ft_printf_fd(pipe_id[1], "%s\n", line);
		free(line);
	}
}
