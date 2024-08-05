/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hitran <hitran@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 15:06:48 by hitran            #+#    #+#             */
/*   Updated: 2024/08/05 22:22:00 by hitran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	excecute_command(t_pipex *pipex, char *command)
{
	char	**splitted_cmd;
	char	*command_path;

	splitted_cmd = split_command(command);
	if (!splitted_cmd)
		exit(1);
	command_path = find_command_path(pipex->envp, splitted_cmd);
	if (!command_path)
	{
		ft_printf_fd(2, "pipex: %s: Command not found\n", *splitted_cmd);
		ft_free_triptr(&splitted_cmd);
		exit(127);
	}
	execve(command_path, splitted_cmd, pipex->envp);
	handle_exec_error(command_path, splitted_cmd);
}

static void	first_command(t_pipex *pipex)
{
	pipex->pid = fork();
	if (pipex->pid == -1)
		handle_fork_error(pipex->pipe_id);
	else if (pipex->pid == 0)
	{
		close(pipex->pipe_id[0]);
		pipex->fd[0] = open(pipex->argv[1], O_RDONLY);
		if (pipex->fd[0] == -1)
			handle_open_error(pipex->argv[1], pipex->pipe_id[1]);
		redirect_fds(pipex->fd[0], 0, pipex->pipe_id[1], 1);
		excecute_command(pipex, pipex->argv[2]);
	}
	close(pipex->pipe_id[1]);
}

static void	last_command(t_pipex *pipex)
{
	pipex->pid = fork();
	if (pipex->pid == -1)
		handle_fork_error(pipex->pipe_id);
	else if (pipex->pid == 0)
	{
		pipex->fd[1] = open(pipex->argv[pipex->argc - 1],
				O_CREAT | O_RDWR | O_TRUNC, 0644);
		if (pipex->fd[1] == -1)
			handle_open_error(pipex->argv[pipex->argc - 1], pipex->pipe_id[0]);
		redirect_fds(pipex->pipe_id[0], 0, pipex->fd[1], 1);
		excecute_command(pipex, pipex->argv[pipex->argc - 2]);
	}
	close(pipex->pipe_id[0]);
	waitpid(pipex->pid, &pipex->error, 0);
}

void	execute_pipex(t_pipex *pipex)
{
	create_pipe(pipex->pipe_id);
	first_command(pipex);
	last_command(pipex);
	while (wait(NULL) > 0)
		;
}
