/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_errors_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hitran <hitran@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 21:58:15 by hitran            #+#    #+#             */
/*   Updated: 2024/08/05 23:38:13 by hitran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	handle_exec_error(char *command_path, char **splitted_cmd)
{
	ft_printf_fd(2, "pipex: %s: %s\n", *splitted_cmd, strerror(errno));
	if (command_path)
		free(command_path);
	ft_free_triptr(&splitted_cmd);
	exit(126);
}

void	handle_open_error(char *name, int pipe_num)
{
	ft_printf_fd(2, "pipex: %s: %s\n", name, strerror(errno));
	close(pipe_num);
	exit(1);
}

void	handle_fork_error(int *fd)
{
	close(fd[0]);
	close(fd[1]);
	perror("pipex: fork\n");
	exit (1);
}

void	handle_read_error(int *fd)
{
	close(fd[0]);
	close(fd[1]);
	perror("pipex: read\n");
	exit (1);
}
