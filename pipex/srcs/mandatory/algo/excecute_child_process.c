/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   excecute_child_process.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hitran <hitran@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 21:24:25 by hitran            #+#    #+#             */
/*   Updated: 2024/07/11 21:25:32 by hitran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	execute_child_process(t_pipex *pipex)
{
	redirect_pipe(pipex, 0, 1);;
	pipex->fd[0] = open(pipex->argv[1], O_RDONLY);
	if (pipex->fd[0] == -1)
	{
		ft_printf_fd(2, "pipex: %s: %s\n", pipex->argv[1], strerror(errno));
		close(pipex->pipe[1]);
		exit(1);
	}
	dup2(pipex->fd[0], 0);
	excecute_command(pipex, pipex->argv[2]);
}
