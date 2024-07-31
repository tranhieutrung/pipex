/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_here_doc_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hitran <hitran@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 13:08:57 by hitran            #+#    #+#             */
/*   Updated: 2024/07/31 22:00:46 by hitran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	read_here_doc(t_pipex *pipex, int *pipe_id)
{
	int		i;
	int		ret;
	char	c;
	char	*line;

	i = 0;
	line = (char *) ft_calloc(BUFFER_SIZE, 1);
	if (!line)
		exit (1);
	ret = read(0, &c, 1);
	if (ret == -1)
		handle_read_error(pipe_id);
	while (ret && c && c != '\n')
	{
		line[i++] = c;
		ret = read(0, &c, 1);
	}
	if (ft_strcmp(line, pipex->argv[2]))
	{
		ft_printf_fd(pipe_id[1], "%s", line);
		ft_printf_fd(pipe_id[1], "%c", '\n');
		read_here_doc(pipex, pipe_id);
	}
	free(line);
}
