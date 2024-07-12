/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_command_path.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hitran <hitran@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 15:11:40 by hitran            #+#    #+#             */
/*   Updated: 2024/07/13 00:28:33 by hitran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	is_valid_path(char *command)
{
	if (ft_strchr(command, '/'))
	{
		if (access(command, F_OK) == 0)
			return (1);
		else
		{
			ft_printf_fd(2,"pipex: %s: No such file or directory\n", command);
			ft_free_strptr(&command);
			exit(127);
		}
	}
	return (0);
}

static char	**find_envp_path(char **envp, char *command)
{
	int		i;
	char	**envp_paths;

	i = 0;
	while (envp[i] && !ft_strnstr(envp[i], "PATH=", 5))
		i++;
	if (!envp[i])
	{
		ft_printf_fd(2,"pipex: %s: No such file or directory\n", command);
		ft_free_strptr(&command);
		exit(127);
	}
	envp_paths = ft_split(envp[i] + 5, ':');
	if (!envp_paths)
		return (NULL);
	return (envp_paths);
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
	if (!command_path)
		return (NULL);
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
		if (!command_path)
		{
			ft_free_strptr(envp_paths);
			return (NULL);
		}
		if (access(command_path, F_OK) == 0)
		{
			ft_free_strptr(envp_paths);
			return (command_path);
		}
		free(command_path);
		i++;
	}
	ft_free_strptr(envp_paths);
	ft_printf_fd(2, "pipex: %s: command not found\n", command);
	return (NULL);
}

char	*find_command_path(t_pipex *pipex, char *command)
{
	char	**envp_paths;
	char	*command_path;

	if (is_valid_path(command))
		return (command);
	envp_paths = find_envp_path(pipex->envp, command);
	if (!envp_paths)
		return (NULL);
	command_path = get_command_path(envp_paths, command);
	if (!command_path)
		return (NULL);
	return (command_path);
}
