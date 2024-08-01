/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hitran <hitran@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 21:15:00 by hitran            #+#    #+#             */
/*   Updated: 2024/08/01 16:20:33 by hitran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void excecute_command(t_pipex *pipex, char *command)
{
    char **splitted_command;
    char *command_path;

    splitted_command = split_command(command);
    if (!splitted_command)
    {
        ft_printf_fd(2, "pipex: split command failed\n");
        exit(1);
    }
    if (ft_strchr(splitted_command[0], '/'))
    {
        if (access(splitted_command[0], F_OK) == 0)
            command_path = ft_strdup(splitted_command[0]);
        else
        {
            ft_printf_fd(2, "pipex: %s: no such file or directory\n", *splitted_command);
            ft_free_triptr(&splitted_command);
            pipex->error = 127;
            exit(pipex->error);
        }
    }
    else
    {
        command_path = find_command_path(pipex->envp, splitted_command);
        if (!command_path)
        {
            ft_printf_fd(2, "pipex: %s: command not found\n", *splitted_command);
            ft_free_triptr(&splitted_command);
            pipex->error = 127;
            exit(pipex->error);
        }
    }
    execve(command_path, splitted_command, pipex->envp);
    handle_exec_error(command_path, splitted_command);
}

static void first_command(t_pipex *pipex, int *pipe_id)
{
    int in_fd;

    close(pipe_id[0]);
    in_fd = open(pipex->argv[1], O_RDONLY);
    if (in_fd == -1)
        handle_open_error(pipex->argv[1], pipe_id[1]);
    redirect_fds(in_fd, 0, pipe_id[1], 1);
    excecute_command(pipex, pipex->argv[2]);
}

static void middle_command(t_pipex *pipex, int *prev_pipe, int *next_pipe, char *command)
{
    close(prev_pipe[1]);
    close(next_pipe[0]);
    redirect_fds(prev_pipe[0], 0, next_pipe[1], 1);
    excecute_command(pipex, command);
}

static void last_command(t_pipex *pipex, int *pipe_id)
{
    int out_fd;

    close(pipe_id[1]);
    out_fd = open(pipex->argv[pipex->argc - 1], O_CREAT | O_RDWR | O_TRUNC, 0644);
    if (out_fd == -1)
        handle_open_error(pipex->argv[pipex->argc - 1], pipe_id[0]);
    redirect_fds(pipe_id[0], 0, out_fd, 1);
    excecute_command(pipex, pipex->argv[pipex->argc - 2]);
}

void execute_pipex(t_pipex *pipex)
{
    int prev_pipe[2];
    int next_pipe[2];
    pid_t pid;
    int i;

    create_pipe(prev_pipe);
	pid = fork();
    if (pid == -1)
        handle_fork_error(prev_pipe[0], prev_pipe[1]);
    else if (pid == 0)
        first_command(pipex, prev_pipe);
    close(prev_pipe[1]);
    waitpid(pid, NULL, 0);
    for (i = 3; i < pipex->argc - 2; i++)
    {
        create_pipe(next_pipe);
        pid = fork();
        if (pid == -1)
            handle_fork_error(prev_pipe[0], next_pipe[1]);
        else if (pid == 0)
            middle_command(pipex, prev_pipe, next_pipe, pipex->argv[i]);
        close(prev_pipe[0]);
        close(prev_pipe[1]);
        prev_pipe[0] = next_pipe[0];
        prev_pipe[1] = next_pipe[1];
        waitpid(pid, NULL, 0);
    }
    pid = fork();
    if (pid == -1)
        handle_fork_error(prev_pipe[0], prev_pipe[1]);
    else if (pid == 0)
        last_command(pipex, prev_pipe);
    close(prev_pipe[0]);
    close(prev_pipe[1]);
    waitpid(pid, &pipex->error, 0);
    while (waitpid(-1, NULL, 0) > 0)
        ;
}
