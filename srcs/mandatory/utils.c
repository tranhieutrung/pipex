/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hitran <hitran@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 21:58:15 by hitran            #+#    #+#             */
/*   Updated: 2024/07/13 22:34:57 by hitran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	handle_error_126(char *command, char **splitted_command)
{
	ft_printf_fd(2, "pipex: %s: Is a directory\n", command);
	ft_free_strptr(splitted_command);
	exit(126);
}

void	handle_error_127(char *command, char **splitted_command)
{
	ft_printf_fd(2, "pipex: %s: command not found\n", command);
	ft_free_strptr(splitted_command);
	exit(127);
}

void	handle_error_exec(char *command_path, char **splitted_command)
{
	if (!access(*splitted_command, F_OK) && !access(*splitted_command, X_OK))
	{
		if (command_path)
			free(command_path);
		if (ft_strchr(*splitted_command, '/'))
			handle_error_126(*splitted_command, splitted_command);
		else
			handle_error_127(*splitted_command, splitted_command);
	}
	ft_printf_fd(2, "pipex: %s: %s\n", command_path, strerror(errno));
	if (command_path)
		free(command_path);
	ft_free_strptr(splitted_command);
	exit(126);
}

void	handle_empty_command(char *trimmed_command, char *command)
{
	if (*trimmed_command == ' ' || !*trimmed_command)
		ft_printf_fd(2, "pipex: %s: command not found\n", command);
	free(trimmed_command);
	exit (127);
}
