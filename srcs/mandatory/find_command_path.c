/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_command_path.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hitran <hitran@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 15:11:40 by hitran            #+#    #+#             */
/*   Updated: 2024/07/12 22:10:49 by hitran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	*ft_is_valid_path(char **cmds)
{
	if (access(cmds[0], F_OK) == 0)
		return (ft_strdup(cmds[0]));
	else
	{
		ft_printf_fd(
			2,
			"%s: %s: No such file or directory\n",
			"pipex", cmds[0]);
		// ft_multiple_free_set_null(&cmds);
		exit(127);
	}
}

static char	**find_env_path(char **envp, char **cmds)
{
	int		i;
	char	**paths;

	i = 0;
	paths = NULL;
	while (envp[i] && !ft_strnstr(envp[i], "PATH=", 5))
		i++;
	if (!envp[i])
	{
		ft_printf_fd(
			2,
			"%s: %s: No such file or directory\n",
			"pipex", cmds[0]);
		// ft_multiple_free_set_null(&cmds);
		exit(127);
	}
	paths = ft_split(envp[i] + 5, ':');
	if (!paths)
		return (NULL);
	return (paths);
}

static char	*find_cmd_full_path(char **paths, char *command)
{
	char	*full_path;
	char	*cmd_full_path;
	int		i;

	i = 0;
	while (paths[i])
	{
		full_path = ft_strjoin(paths[i], "/");
		// if (!full_path)
		// 	ft_return_multiple_free_set_null(&paths);
		cmd_full_path = ft_strjoin(full_path, command);
		free(full_path);
		// if (!cmd_full_path)
		// 	ft_return_multiple_free_set_null(&paths);
		if (access(cmd_full_path, F_OK) == 0)
		{
			// ft_multiple_free_set_null(&paths);
			return (cmd_full_path);
		}
		free(cmd_full_path);
		i++;
	}
	// ft_multiple_free_set_null(&paths);
	return (NULL);
}

char	*find_command_path(t_pipex *pipex, char **commands)
{
	char	**paths;
	char	*cmd_full_path;

	if (ft_strchr(*commands, '/'))
		return (ft_is_valid_path(commands));
	paths = find_env_path(pipex->envp, commands);
	if (!paths)
		return (NULL);
	cmd_full_path = find_cmd_full_path(paths, *commands);
	if (!cmd_full_path)
	{
		return (NULL);
	}
	return (cmd_full_path);
}
