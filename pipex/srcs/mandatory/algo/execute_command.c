/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hitran <hitran@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 21:24:34 by hitran            #+#    #+#             */
/*   Updated: 2024/07/11 21:25:22 by hitran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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