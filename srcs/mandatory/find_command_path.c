/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_command_path.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hitran <hitran@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 15:11:40 by hitran            #+#    #+#             */
/*   Updated: 2024/07/14 15:15:57 by hitran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	**find_envp_path(char **envp)
{
	int		i;

	i = 0;
	while (envp[i] && !ft_strnstr(envp[i], "PATH=", 5))
		i++;
	if (!envp[i])
		return (NULL);
	return (ft_split(envp[i] + 5, ':'));
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
	int		i;

	i = 0;
	while (envp_paths[i])
	{
		command_path = join_command_path(envp_paths[i], command);
		if (!command_path || access(command_path, F_OK) == 0)
			return (command_path);
		free(command_path);
		i++;
	}
	return (NULL);
}

char	*find_command_path(char **envp, char **splitted_command)
{
	char	**envp_paths;
	char	*command_path;

	if (ft_strchr(*splitted_command, '/'))
	{
		if (access(*splitted_command, F_OK) == 0)
			return (ft_strdup(*splitted_command));
		else
			return (NULL);
	}
	envp_paths = find_envp_path(envp);
	if (!envp_paths)
		return (NULL);
	command_path = get_command_path(envp_paths, *splitted_command);
	ft_free_strptr(envp_paths);
	return (command_path);
}
