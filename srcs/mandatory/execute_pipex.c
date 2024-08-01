/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hitran <hitran@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 21:24:26 by hitran            #+#    #+#             */
/*   Updated: 2024/08/02 00:01:14 by hitran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void first_command(t_pipex *pipex)
{
	int in_fd;

	pipex->pid = fork();
	if (pipex->pid == -1)
		handle_fork_error(pipex->pipe_id[0], pipex->pipe_id[1]);
	else if (pipex->pid == 0)
	{
        close(pipex->pipe_id[0]);
        in_fd = open(pipex->argv[1], O_RDONLY);
        if (in_fd == -1)
            handle_open_error(pipex->argv[1], pipex->pipe_id[1]);
        redirect_fds(in_fd, 0, pipex->pipe_id[1], 1);
        excecute_command(pipex, pipex->argv[2]);
    }
    close(pipex->pipe_id[1]);
	// waitpid(pipex->pid, &pipex->temp_error, 0);
    // if (pipex->temp_error > pipex->error)
    //     pipex->error = pipex->temp_error;
}

static void middle_command(t_pipex *pipex, int *next_pipe, int cmd_index)
{
    create_pipe(next_pipe);
	pipex->pid = fork();
	if (pipex->pid == -1)
		handle_fork_error(pipex->pipe_id[0], next_pipe[1]);
	else if (pipex->pid == 0)
	{
        close(pipex->pipe_id[1]);
        close(next_pipe[0]);
        redirect_fds(pipex->pipe_id[0], 0, next_pipe[1], 1);
        excecute_command(pipex, pipex->argv[cmd_index]);
    }
    close(pipex->pipe_id[0]);
	close(pipex->pipe_id[1]);
	pipex->pipe_id[0] = next_pipe[0];
	pipex->pipe_id[1] = next_pipe[1];
    // waitpid(pipex->pid, &pipex->temp_error, 0);
    // if (pipex->temp_error > pipex->error)
    //     pipex->error = pipex->temp_error;
}

static void last_command(t_pipex *pipex)
{
	int out_fd;

    pipex->pid = fork();
	if (pipex->pid == -1)
		handle_fork_error(pipex->pipe_id[0], pipex->pipe_id[1]);
	else if (pipex->pid == 0)
	{
        close(pipex->pipe_id[1]);
        out_fd = open(pipex->argv[pipex->argc - 1], O_CREAT | O_RDWR | O_TRUNC, 0644);
        if (out_fd == -1)
            handle_open_error(pipex->argv[pipex->argc - 1], pipex->pipe_id[0]);
        redirect_fds(pipex->pipe_id[0], 0, out_fd, 1);
	    excecute_command(pipex, pipex->argv[pipex->argc - 2]);
    }
	close(pipex->pipe_id[0]);
	close(pipex->pipe_id[1]);
	waitpid(pipex->pid, &pipex->error, 0);
    // waitpid(pipex->pid, &pipex->temp_error, 0);
    // if (pipex->temp_error > pipex->error)
    //     pipex->error = pipex->temp_error;
}

void execute_pipex(t_pipex *pipex)
{
	int next_pipe[2];
	int index;

	create_pipe(pipex->pipe_id);
	first_command(pipex);
	index = 3;
    while (index < pipex->argc - 2)
        middle_command(pipex, next_pipe, index++);
    last_command(pipex);
    while (waitpid(-1, NULL, 0) > 0)
        ;
}

