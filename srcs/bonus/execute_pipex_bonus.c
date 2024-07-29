/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipex_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hitran <hitran@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 21:15:00 by hitran            #+#    #+#             */
/*   Updated: 2024/07/29 12:27:58 by hitran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	redirect_fds(int from_fd1, int to_fd1, int from_fd2, int to_fd2)
{
	dup2(from_fd1, to_fd1);
	close(from_fd1);
	dup2(from_fd2, to_fd2);
	close(from_fd2);
}

static void	excecute_command(t_pipex *pipex, char *command)
{
	char	**splitted_command;
	char	*command_path;

	splitted_command = split_command(command);
	if (!splitted_command)
		handle_error("split command failed", 1, NULL);
	command_path = find_command_path(pipex->envp, splitted_command);
	if (!command_path)
		handle_error("command not found", 127, splitted_command);
	execve(command_path, splitted_command, pipex->envp);
	handle_exec_error(command_path, splitted_command);
}

static void	execute_first_commands(t_pipex *pipex, int *pipe_id)
{
	pipex->fd[0] = open(pipex->argv[1], O_RDONLY);
	if (pipex->fd[0] == -1)
		handle_open_error(pipex->argv[1], pipe_id[1]);
	redirect_fds(pipex->fd[0], 0, pipe_id[1], 1);
	excecute_command(pipex, pipex->argv[2]);
}

static void	execute_last_command(t_pipex *pipex, int *pipe_id)
{
	pid_t	pid;
	
	pid = fork();
	if (pid == -1)
		handle_fork_error(pipe_id[0], pipex->fd[1]);
	else if (pid == 0)
	{
		pipex->fd[1] = open(pipex->argv[pipex->argc - 1],
				O_CREAT | O_RDWR | O_TRUNC, 00700);
		if (pipex->fd[1] == -1)
			handle_open_error(pipex->argv[pipex->argc - 1], pipe_id[0]);
		redirect_fds(pipe_id[0], 0, pipex->fd[1], 1);
		excecute_command(pipex, pipex->argv[3]);
	}
	else
		waitpid(pid, &pipex->error, 0);
}

void	execute_pipex(t_pipex *pipex)
{
	pid_t	pid;
	int		pipe_id[2];

	if (pipe(pipe_id) == -1)
	{
		perror("pipex: pipe\n");
		exit (1);
	}
	pid = fork();
	if (pid == -1)
		handle_fork_error(pipe_id[0], pipe_id[1]);
	else if (pid == 0)
	{
		close(pipe_id[0]);
		execute_first_commands(pipex, pipe_id);
		close(pipe_id[1]);
	}
	else
	{
		close(pipe_id[1]);
		execute_last_command(pipex, pipe_id);
		close(pipe_id[0]);
		waitpid(pid, NULL, 0);
	}
}
