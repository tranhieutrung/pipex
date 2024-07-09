/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_pipe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hitran <hitran@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 23:55:03 by hitran            #+#    #+#             */
/*   Updated: 2024/07/08 08:59:53 by hitran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void redirect_pipe(t_pipex *pipex, int source, int dest)
{
    close(pipex->pipe[source]);         
    dup2(pipex->pipe[dest], dest);      
    close(pipex->pipe[dest]);           
}

static void	execute_command(t_pipex *pipex, char *cmd)
{
	pipex->pid = fork();
	if (pipex->pid == 0)
	{
		redirect_pipe(pipex, 0, 1);
		pipex->cmdargs = split_word(cmd);
		pipex->path = find_path(pipex);
		if (access(pipex->path, F_OK | X_OK) != 0
			&& ft_strchr(pipex->cmdargs[0], '/'))
		{
			perror(".ERROR: Command Not Found.\n");
			ft_free_strptr(pipex->cmdargs);
			exit(1);
		}
		execve(pipex->path, pipex->cmdargs, pipex->envi);
		write(2, ".ERROR: Command Not Found.\n", 27);
		ft_free_strptr(pipex->cmdargs);
		exit(1);
	}
	redirect_pipe(pipex, 1, 0);
}

void	handle_pipe(t_pipex *pipex, char **argv)
{
	dup2(pipex->fd[0], 0);
	pipe(pipex->pipe);
	execute_command(pipex, argv[2]);
	close(pipex->fd[0]);
	dup2(pipex->fd[1], 1);
	execute_command(pipex, argv[3]);
	close(pipex->fd[1]);
	waitpid(-1, NULL, 0);
}
