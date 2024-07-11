/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_parent_process.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hitran <hitran@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 21:23:52 by hitran            #+#    #+#             */
/*   Updated: 2024/07/11 21:25:18 by hitran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	execute_parent_process(t_pipex *pipex)
{
	close(pipex->fd[0]);
	pipex->fd[1] = open(pipex->argv[pipex->argc - 1],
					O_CREAT | O_RDWR | O_TRUNC, 00700);
	if (pipex->fd[1] == -1)
	{
		ft_printf_fd(2, "pipex: %s: %s\n",
			pipex->argv[pipex->argc - 1], strerror(errno));
		close(pipex->pipe[0]);
		exit(1);
	}
	pipex->pid = fork();
	if (pipex->pid == -1)
	{
		close(pipex->pipe[0]);
		close(pipex->pipe[1]);
		perror("pipex: fork");
		exit (1);
	}
	else if (pipex->pid == 0)
	{
		dup2(pipex->fd[1], 1);
		excecute_command(pipex, pipex->argv[3]);
	}
	else
		waitpid(pid, &(shell->error), 0);
}