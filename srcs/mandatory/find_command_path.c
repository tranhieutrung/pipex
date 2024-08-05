/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_command_path.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hitran <hitran@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 15:11:40 by hitran            #+#    #+#             */
/*   Updated: 2024/08/05 23:07:17 by hitran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	**find_envp_path(char **envp)
{
	while (*envp && !ft_strnstr(*envp, "PATH=", 5))
		envp++;
	if (!*envp)
		return (NULL);
	return (ft_split(*envp + 5, ':'));
}

static char	*join_command_path(char *envp_path, char *command)
{
	char	*command_dir;
	char	*command_path;

	command_dir = ft_strjoin(envp_path, "/");
	if (!command_dir)
		return (NULL);
	command_path = ft_strjoin(command_dir, command);
	free(command_dir);
	return (command_path);
}

static char	*get_command_path(char **envp_paths, char *command)
{
	char	*command_path;

	while (*envp_paths)
	{
		command_path = join_command_path(*(envp_paths++), command);
		if (!command_path || access(command_path, F_OK) == 0)
			return (command_path);
		free(command_path);
	}
	return (NULL);
}

char	*find_command_path(char **envp, char **splitted_cmd)
{
	char	**envp_paths;
	char	*command_path;

	if (ft_strchr(*splitted_cmd, '/'))
	{
		if (access(*splitted_cmd, F_OK) == 0)
			return (ft_strdup(*splitted_cmd));
		else
		{
			ft_printf_fd(2, "pipex: %s: No such file or directory\n",
				*splitted_cmd);
			ft_free_triptr(&splitted_cmd);
			exit(127);
		}
	}
	envp_paths = find_envp_path(envp);
	if (!envp_paths)
		return (NULL);
	command_path = get_command_path(envp_paths, *splitted_cmd);
	ft_free_triptr(&envp_paths);
	return (command_path);
}
