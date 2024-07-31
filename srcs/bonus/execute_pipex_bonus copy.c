/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipex_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hitran <hitran@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 21:15:00 by hitran            #+#    #+#             */
/*   Updated: 2024/07/31 11:38:56 by hitran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static void	redirect_fds(int from_fd1, int to_fd1, int from_fd2, int to_fd2)
{
    if (dup2(from_fd1, to_fd1) == -1)
    {
        perror("pipex: dup2");
        exit(1);
    }
    close(from_fd1);
    if (dup2(from_fd2, to_fd2) == -1)
    {
        perror("pipex: dup2");
        exit(1);
    }
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

static void	execute_child_process(t_pipex *pipex, int *pipe_id, int cmd_index)
{
	int in_fd;

	if (cmd_index == 3 && ft_strcmp(pipex->argv[1], "here_doc") == 0)
	{
		close(pipe_id[0]);
		read_here_doc(pipex, pipe_id);
		dup2(pipe_id[1], 1);
		close(pipe_id[1]);
	}
	else if (cmd_index == 2)
	{
		close(pipe_id[0]);
		in_fd = open(pipex->argv[1], O_RDONLY);
		if (in_fd == -1)
			handle_open_error(pipex->argv[1], pipe_id[1]);
		redirect_fds(in_fd, 0, pipe_id[1], 1);
	}
	else
		redirect_fds(pipe_id[0], 0, pipe_id[1], 1);
	excecute_command(pipex, pipex->argv[cmd_index]);
}

static void	execute_parent_process(t_pipex *pipex, int *pipe_id)
{
	pid_t	pid;
	int		out_fd;
	
	pid = fork();
	if (pid == -1)
		handle_fork_error(pipe_id[0], pipe_id[1]);
	else if (pid == 0)
	{
		// close(pipe_id[1]);
		out_fd = open(pipex->argv[pipex->argc - 1],
				O_CREAT | O_RDWR | O_TRUNC, 00644);
		if (out_fd == -1)
			handle_open_error(pipex->argv[pipex->argc - 1], pipe_id[0]);
		redirect_fds(pipe_id[0], 0, out_fd, 1);
		excecute_command(pipex, pipex->argv[pipex->argc - 2]);
	}
	else
	{
		close(pipe_id[0]);
		waitpid(pid, &pipex->error, 0);
	}
}

void	execute_pipex(t_pipex *pipex, int cmd_index)
{
	pid_t	pid;
	int		pipe_id[2];

	if (cmd_index == 2 && ft_strcmp(pipex->argv[1], "here_doc") == 0)
		cmd_index = 3;
	if (pipe(pipe_id) == -1)
	{
		perror("pipex: pipe\n");
		exit (1);
	}
	pid = fork();
	if (pid == -1)
		handle_fork_error(pipe_id[0], pipe_id[1]);
	else if (pid == 0)
		execute_child_process(pipex, pipe_id, cmd_index);
	else
	{
		close(pipe_id[1]);
		if (++cmd_index < pipex->argc - 2)
			execute_pipex(pipex, cmd_index);
		else
			execute_parent_process(pipex, pipe_id);
		close(pipe_id[0]);
		waitpid(pid, NULL, 0);
	}
}
