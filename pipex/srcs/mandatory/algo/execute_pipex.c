/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hitran <hitran@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 21:22:23 by hitran            #+#    #+#             */
/*   Updated: 2024/07/11 21:25:59 by hitran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	redirect_pipe(t_pipex *pipex, int source, int dest)
{
    close(pipex->pipe[source]);         
    dup2(pipex->pipe[dest], dest);      
    close(pipex->pipe[dest]);           
}

void	execute_pipex(t_pipex *pipex)
{
	pipex->pid = fork();
	if (pipex->pid == -1)
	{
		close(pipex->pipe[0]);
		close(pipex->pipe[1]);
		perror("pipex: fork");
		exit (1);
	}
	else if (pipex->pid == 0)
		execute_child_process(pipex);
	else
		execute_parent_process(pipex);
	exit (1);
}
