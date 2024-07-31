/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipex_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hitran <hitran@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 21:15:00 by hitran            #+#    #+#             */
/*   Updated: 2024/08/01 00:00:46 by hitran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void create_pipe(int *pipe_id)
{
	if (pipe(pipe_id) == -1)
	{
		perror("pipex: pipe\n");
		exit (1);
	}
}

static void	redirect_fds(int from_fd1, int to_fd1, int from_fd2, int to_fd2)
{
	if (dup2(from_fd1, to_fd1) == -1 || dup2(from_fd2, to_fd2) == -1)
	{
		perror("pipex: dup2");
		close(from_fd1);
		close(from_fd2);
		exit(1);
	}
	close(from_fd1);
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

static void	first_commands(t_pipex *pipex, int cmd_index)
{
	int	hd_pipe[2];
	int pre_pipe_id;
	int	in_fd;
	
	pipex->pid = fork();
	if (pipex->pid == -1)
		handle_fork_error(pipex->pipe_id);
	else if (pipex->pid == 0)
	{
		if (cmd_index == 3 && ft_strcmp(pipex->argv[1], "here_doc") == 0)
		{
			create_pipe(hd_pipe);
			read_here_doc(pipex, hd_pipe);
			close(hd_pipe[1]);
			create_pipe(pipex->pipe_id);
			close(pipex->pipe_id[0]);
			redirect_fds(hd_pipe[0], 0, pipex->pipe_id[1], 1);
		}
		else if (cmd_index == 2)
		{
			create_pipe(pipex->pipe_id);
			close(pipex->pipe_id[0]);
			in_fd = open(pipex->argv[1], O_RDONLY);
			if (in_fd == -1)
				handle_open_error(pipex->argv[1], pipex->pipe_id[1]);
			redirect_fds(in_fd, 0, pipex->pipe_id[1], 1);
		}
		else
		{
			pre_pipe_id = pipex->pipe_id[0];
			create_pipe(pipex->pipe_id);
			close(pipex->pipe_id[0]);
			redirect_fds(pre_pipe_id, 0, pipex->pipe_id[1], 1);
		}
		excecute_command(pipex, pipex->argv[cmd_index]);
	}
	close (pipex->pipe_id[1]);
}

static void	last_command(t_pipex *pipex)
{
	int out_fd;
	
	pipex->pid = fork();
	if (pipex->pid == -1)
		handle_fork_error(pipex->pipe_id);
	else if (pipex->pid == 0)
	{
		if (ft_strcmp(pipex->argv[1], "here_doc") == 0)
			out_fd = open(pipex->argv[pipex->argc - 1],
				O_CREAT | O_RDWR | O_APPEND, 0644);
		else
			out_fd = open(pipex->argv[pipex->argc - 1],
				O_CREAT | O_RDWR | O_TRUNC, 0644);
		if (out_fd == -1)
			handle_open_error(pipex->argv[pipex->argc - 1], pipex->pipe_id[0]);
		redirect_fds(pipex->pipe_id[0], 0, out_fd, 1);
		excecute_command(pipex, pipex->argv[pipex->argc - 2]);
	}
	else
		waitpid(pipex->pid, &pipex->error, 0);
}

void	execute_pipex(t_pipex *pipex)
{
	int		cmd_index;

	cmd_index = 2;
	if (ft_strcmp(pipex->argv[1], "here_doc") == 0)
		cmd_index = 3;
	while (cmd_index <= pipex->argc - 2)
	{
		if (cmd_index < pipex->argc - 2)	
			first_commands(pipex, cmd_index);
		else
		{
			last_command(pipex);
			close(pipex->pipe_id[0]);
		}
		cmd_index++;
	}
	waitpid(-1, NULL, 0); //wait for all child processes
}
