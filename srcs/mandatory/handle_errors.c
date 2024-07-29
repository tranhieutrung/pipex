/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hitran <hitran@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 21:58:15 by hitran            #+#    #+#             */
/*   Updated: 2024/07/29 14:48:36 by hitran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	handle_exec_error(char *command_path, char **splitted_command)
{
	ft_printf_fd(2, "pipex: %s: %s\n", *splitted_command, strerror(errno));
	if (command_path)
		free(command_path);
	ft_free_triptr(&splitted_command);
	exit(126);
}

void	handle_empty_command(char *trimmed_command, char *command)
{
	ft_printf_fd(2, "pipex: %s: command not found\n", command);
	free(trimmed_command);
	exit (127);
}

void handle_open_error(char *name, int pipe_num)
{
	ft_printf_fd(2, "pipex: %s: %s\n", name, strerror(errno));
	close(pipe_num);
	exit(1);
}

void handle_fork_error(int fd1, int fd2)
{
	close(fd1);
	close(fd2);
	perror("pipex: fork\n");
	exit (1);
}
