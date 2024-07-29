/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipex_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hitran <hitran@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 21:15:00 by hitran            #+#    #+#             */
/*   Updated: 2024/07/29 14:46:45 by hitran           ###   ########.fr       */
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
	{
		ft_printf_fd(2, "pipex: split command failed\n");
		exit (1);
	}
	command_path = find_command_path(pipex->envp, splitted_command);
	if (!command_path)
	{
		ft_printf_fd(2, "pipex: %s: command not found\n", *splitted_command);
		ft_free_triptr(&splitted_command);
		exit (127);
	}
	execve(command_path, splitted_command, pipex->envp);
	handle_exec_error(command_path, splitted_command);
}

void	handle_error(char *message, int error_number, char **command)
{
	if(!command)
		ft_printf_fd(2, "pipex: %s\n", message);
	else
	{
		ft_printf_fd(2, "pipex: %s: %s\n", *command, message);
		ft_free_triptr(&command);
	}
	exit(error_number);
}

static void	execute_first_commands(t_pipex *pipex, int *pipe_id)
{
	int command_index;

	command_index = 2;
	if (command_index < pipex->argc - 2)
		execute_next_command(pipex, pipe_id, command_index);
	pipex->fd[0] = open(pipex->argv[1], O_RDONLY);
	if (pipex->fd[0] == -1)
		handle_open_error(pipex->argv[1], pipe_id[1]);
	redirect_fds(pipex->fd[0], 0, pipe_id[1], 1);
	excecute_command(pipex, pipex->argv[2]);
	command_index = 3;

}

static void	execute_first_commands(t_pipex *pipex, int *pipe_id, int cmd_index)
{
	cmd_index++;
	if (cmd_index == 2)
	{
		pipex->fd[0] = open(pipex->argv[1], O_RDONLY);
		if (pipex->fd[0] == -1)
			handle_open_error(pipex->argv[1], pipe_id[1]);
		redirect_fds(pipex->fd[0], 0, pipe_id[1], 1);
		excecute_command(pipex, pipex->argv[2]);
	}
	else if (cmd_index < pipex->argc - 2)
		execute_next_command(pipex, pipe_id, cmd_index);
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
		execute_first_commands(pipex, pipe_id, 1);
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
