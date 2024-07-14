/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hitran <hitran@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 21:58:15 by hitran            #+#    #+#             */
/*   Updated: 2024/07/14 11:11:39 by hitran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	handle_error(char *message, int error_number, char **command)
{
	if(!command)
		ft_printf_fd(2, "pipex: %s\n", message);
	else
	{
		ft_printf_fd(2, "pipex: %s: %s\n", *command, message);
		ft_free_strptr(command);
	}
	exit(error_number);
}

void	handle_exec_error(char *command_path, char **splitted_command)
{
	// if (!access(*splitted_command, F_OK) && !access(*splitted_command, X_OK))
	// {
	// 	if (command_path)
	// 		free(command_path);
	// 	if (ft_strchr(*splitted_command, '/'))
	// 		handle_error("is a directory", 126, splitted_command);
	// 	else
	// 		handle_error("command not found", 127, splitted_command);
	// }
	ft_printf_fd(2, "pipex: %s: %s\n", command_path, strerror(errno));
	if (command_path)
		free(command_path);
	ft_free_strptr(splitted_command);
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