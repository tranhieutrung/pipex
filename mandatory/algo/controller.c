/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controller.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hitran <hitran@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 23:55:03 by hitran            #+#    #+#             */
/*   Updated: 2024/07/07 23:55:07 by hitran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	cleaner_matrix(char **matrix)
{
	int	i;

	i = -1;
	while (matrix[++i])
		free(matrix[i]);
	free(matrix);
}

static void	closer(t_pipex *pipex, int option1, int option2)
{
	close(pipex->pipe[option1]);
	dup2(pipex->pipe[option2], option2);
	close(pipex->pipe[option2]);
}

static void	executer(t_pipex *pipex, char *cmd)
{
	pipex->pid = fork();
	if (pipex->pid == 0)
	{
		closer(pipex, 0, 1);
		pipex->cmdargs = spliter(cmd);
		pipex->path = pathfinder(pipex);
		if (access(pipex->path, F_OK | X_OK) != 0
			&& ft_strchr(pipex->cmdargs[0], '/'))
		{
			perror(".ERROR: Command Not Found.\n");
			cleaner_matrix(pipex->cmdargs);
			exit(1);
		}
		execve(pipex->path, pipex->cmdargs, pipex->envi);
		write(2, ".ERROR: Command Not Found.\n", 27);
		cleaner_matrix(pipex->cmdargs);
		exit(1);
	}
	closer(pipex, 1, 0);
}

void	cmd_controller(t_pipex *pipex, int cmds_size, char **cmds, int i)
{
	dup2(pipex->fd[0], 0);
	while (++i <= cmds_size - 2)
	{
		if (i < cmds_size - 2)
		{
			pipe(pipex->pipe);
			executer(pipex, cmds[i]);
		}
		else
		{
			close(pipex->fd[0]);
			dup2(pipex->fd[1], 1);
			close(pipex->fd[1]);
			executer(pipex, cmds[i]);
		}
	}
	waitpid(-1, NULL, 0);
}
