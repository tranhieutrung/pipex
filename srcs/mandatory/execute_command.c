/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hitran <hitran@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 21:26:30 by hitran            #+#    #+#             */
/*   Updated: 2024/08/01 21:28:49 by hitran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void    excecute_command(t_pipex *pipex, char *command)
{
	char	**splitted_command;
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
		{
			command_path = ft_strdup(splitted_command[0]);
			if (!command_path)
			{
				ft_printf_fd(2, "pipex: strdup fails\n");
				ft_free_triptr(&splitted_command);
				exit(1);
			}
		}
		else
		{
			ft_printf_fd(2, "pipex: %s: no such file or directory\n", *splitted_command);
			ft_free_triptr(&splitted_command);
			exit(127);
		}
	}
	else
	{
		command_path = find_command_path(pipex->envp, splitted_command);
		if (!command_path)
		{
			ft_printf_fd(2, "pipex: %s: command not found\n", *splitted_command);
			ft_free_triptr(&splitted_command);
			exit(127);
		}
	}
	execve(command_path, splitted_command, pipex->envp);
	handle_exec_error(command_path, splitted_command);
}
