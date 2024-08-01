/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hitran <hitran@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 12:56:32 by hitran            #+#    #+#             */
/*   Updated: 2024/08/01 12:58:24 by hitran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void create_pipe(int *pipe_id)
{
	if (pipe(pipe_id) == -1)
	{
		perror("pipex: pipe\n");
		exit (1);
	}
}

void	redirect_fds(int from_fd1, int to_fd1, int from_fd2, int to_fd2)
{
	if (dup2(from_fd1, to_fd1) == -1 || dup2(from_fd2, to_fd2) == -1)
	{
		perror("pipex: dup2");
		close(from_fd1);
		close(from_fd2);
		exit(1);
	}
	close(from_fd1);
	close(from_fd2);
}
