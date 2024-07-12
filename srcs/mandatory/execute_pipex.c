/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hitran <hitran@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 21:15:00 by hitran            #+#    #+#             */
/*   Updated: 2024/07/13 00:05:21 by hitran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	ft_dup2(int from_fd1, int to_fd1, int from_fd2, int to_fd2)
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
		exit(1);
	}
	command_path = find_command_path(pipex, *splitted_command);
	if (!command_path || (access(command_path, F_OK | X_OK) != 0
			&& ft_strchr(*splitted_command, '/')))
	{
		ft_printf_fd(2, "pipex: %s: command not found\n", *splitted_command);
		ft_free_strptr(splitted_command);
		exit(127);
	}
	execve(command_path, splitted_command, pipex->envp);
	ft_printf_fd(2, "execve fail: %s\n", strerror(errno));
	exit (1);
}

static void	execute_child_process(t_pipex *pipex)
{
	pipex->fd[0] = open(pipex->argv[1], O_RDONLY);
	if (pipex->fd[0] == -1)
	{
		ft_printf_fd(2, "pipex: %s: %s\n", pipex->argv[1], strerror(errno));
		close(pipex->pipe[1]);
		exit(1);
	}
	ft_dup2(pipex->fd[0], 0, pipex->pipe[1], 1);
	excecute_command(pipex, pipex->argv[2]);
}

static void	execute_parent_process(t_pipex *pipex)
{
	pipex->pid = fork();
	if (pipex->pid == -1)
	{
		close(pipex->pipe[0]);
		close(pipex->fd[1]);
		perror("pipex: fork\n");
		exit (1);
	}
	else if (pipex->pid == 0)
	{
		pipex->fd[1] = open(pipex->argv[pipex->argc - 1],
				O_CREAT | O_RDWR | O_TRUNC, 00700);
		if (pipex->fd[1] == -1)
		{
			ft_printf_fd(2, "pipex: %s: %s\n",
				pipex->argv[pipex->argc - 1], strerror(errno));
			close(pipex->pipe[0]);
			exit(1);
		}
		ft_dup2(pipex->pipe[0], 0, pipex->fd[1], 1);
		excecute_command(pipex, pipex->argv[3]);
	}
	else
		waitpid(pipex->pid, NULL, 0);
}

void	execute_pipex(t_pipex *pipex)
{
	pipex->pid = fork();
	if (pipex->pid == -1)
	{
		close(pipex->pipe[0]);
		close(pipex->pipe[1]);
		perror("pipex: fork\n");
		exit (1);
	}
	else if (pipex->pid == 0)
	{
		close(pipex->pipe[0]);
		execute_child_process(pipex);
	}
	else
	{
		close(pipex->pipe[1]);
		execute_parent_process(pipex);
		close(pipex->pipe[0]);
		waitpid(pipex->pid, NULL, 0);
	}
}
