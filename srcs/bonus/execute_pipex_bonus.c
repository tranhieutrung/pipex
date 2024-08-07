/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipex_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hitran <hitran@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 15:06:57 by hitran            #+#    #+#             */
/*   Updated: 2024/08/07 10:09:22 by hitran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	excecute_command(t_pipex *pipex, char *command)
{
	char	**splitted_cmd;
	char	*command_path;

	splitted_cmd = split_command(command);
	if (!splitted_cmd)
		exit(1);
	command_path = find_command_path(pipex->envp, splitted_cmd);
	if (!command_path)
		handle_cmd_error(splitted_cmd, "Command not found", 1);
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
		if (ft_strcmp(pipex->argv[1], "here_doc") == 0)
		{
			create_pipe(pipex->hd_pipe_id);
			read_here_doc(pipex, pipex->hd_pipe_id);
			close (pipex->hd_pipe_id[1]);
			redirect_fds(pipex->hd_pipe_id[0], 0, pipex->pipe_id[1], 1);
			excecute_command(pipex, pipex->argv[3]);
		}
		else
		{
			pipex->fd[0] = open(pipex->argv[1], O_RDONLY);
			if (pipex->fd[0] == -1)
				handle_open_error(pipex->argv[1], pipex->pipe_id[1]);
			redirect_fds(pipex->fd[0], 0, pipex->pipe_id[1], 1);
			excecute_command(pipex, pipex->argv[2]);
		}
	}
}

static void	middle_command(t_pipex *pipex, int cmd_index)
{
	close(pipex->pipe_id[1]);
	create_pipe(pipex->next_pipe);
	pipex->pid = fork();
	if (pipex->pid == -1)
	{
		close (pipex->pipe_id[0]);
		handle_fork_error(pipex->next_pipe);
	}
	else if (pipex->pid == 0)
	{
		close(pipex->next_pipe[0]);
		redirect_fds(pipex->pipe_id[0], 0, pipex->next_pipe[1], 1);
		excecute_command(pipex, pipex->argv[cmd_index]);
	}
	redirect_fds(pipex->next_pipe[0], pipex->pipe_id[0],
		pipex->next_pipe[1], pipex->pipe_id[1]);
}

static void	last_command(t_pipex *pipex)
{
	close(pipex->pipe_id[1]);
	pipex->pid = fork();
	if (pipex->pid == -1)
		handle_fork_error(pipex->pipe_id);
	else if (pipex->pid == 0)
	{
		if (ft_strcmp(pipex->argv[1], "here_doc") == 0)
			pipex->fd[1] = open(pipex->argv[pipex->argc - 1],
					O_CREAT | O_RDWR | O_APPEND, 0644);
		else
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
	int	index;

	create_pipe(pipex->pipe_id);
	first_command(pipex);
	index = 3;
	if (ft_strcmp(pipex->argv[1], "here_doc") == 0)
		index = 4;
	while (index < pipex->argc - 2)
		middle_command(pipex, index++);
	last_command(pipex);
	while (wait(NULL) > 0)
		;
}
