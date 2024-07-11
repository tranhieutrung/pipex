/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hitran <hitran@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 23:54:26 by hitran            #+#    #+#             */
/*   Updated: 2024/07/11 21:20:53 by hitran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	redirect_pipe(t_pipex *pipex, int source, int dest)
{
    close(pipex->pipe[source]);         
    dup2(pipex->pipe[dest], dest);      
    close(pipex->pipe[dest]);           
}

void	excecute_command(t_pipex *pipex, char *command)
{
	char	**splitted_command;
	char	*command_path;

	splitted_command = split_command(command);
	if (!splitted_command)
		exit (1);
	command_path = find_command_path(pipex, command);
	if(!command_path)
	{
		ft_printf_fd(2, "pipex: %s: command not found\n",  *splitted_command);
		ft_free_strptr(splitted_command);
		exit (1);
	}
	if (access(command_path, F_OK | X_OK) != 0
		&& ft_strchr(*splitted_command, '/'))
	{
		ft_printf_fd(2, "pipex: %s: command not found\n",  *splitted_command);
		ft_free_strptr(splitted_command);
		exit(1);
	}
	execve(command_path, splitted_command, pipex->envp);
	exit (1);
}

void	execute_child_process(t_pipex *pipex)
{
	redirect_pipe(pipex, 0, 1);;
	pipex->fd[0] = open(pipex->argv[1], O_RDONLY);
	if (pipex->fd[0] == -1)
	{
		ft_printf_fd(2, "pipex: %s: %s\n", pipex->argv[1], strerror(errno));
		close(pipex->pipe[1]);
		exit(1);
	}
	dup2(pipex->fd[0], 0);
	excecute_command(pipex, pipex->argv[2]);
}

void	execute_parent_process(t_pipex *pipex)
{
	close(pipex->fd[0]);
	pipex->fd[1] = open(pipex->argv[pipex->argc - 1],
					O_CREAT | O_RDWR | O_TRUNC, 00700);
	if (pipex->fd[1] == -1)
	{
		ft_printf_fd(2, "pipex: %s: %s\n",
			pipex->argv[pipex->argc - 1], strerror(errno));
		close(pipex->pipe[0]);
		exit(1);
	}
	pipex->pid = fork();
	if (pipex->pid == -1)
	{
		close(pipex->pipe[0]);
		close(pipex->pipe[1]);
		perror("pipex: fork");
		exit (1);
	}
	else if (pipex->pid == 0)
	{
		dup2(pipex->fd[1], 1);
		excecute_command(pipex, pipex->argv[3]);
	}
	else
		waitpid(pid, &(shell->error), 0);
}

static void	execute_pipex(t_pipex *pipex)
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

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;

	if (argc != 5)
	{
		ft_printf_fd(2, "pipex: invalid number of arguments.\n");
		return (1);
	}
	pipex.argc = argc;
	pipex.argv = argv;
	pipex.envp = envp;
	if (pipe(pipex->pipe) == -1)
	{
		perror("pipex: pipe");
		return (1);
	}
	execute_pipex(&pipex);
	return (0);
}
