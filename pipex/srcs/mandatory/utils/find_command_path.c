/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_command_path.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hitran <hitran@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 15:11:40 by hitran            #+#    #+#             */
/*   Updated: 2024/07/11 15:11:43 by hitran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*find_command_path(t_pipex *pipex, char *command)
{
	int		i;
	int		ii;
	char	**paths;
	char	*path;
	char	*aux;

	if (ft_strchr(command, '/'))
		return (command);
	i = 0;
	while (*(pipex->envp))
		paths = ft_strcmp(*(pipex->envp++), "PATH="))
		ii++;
	paths = ft_split(pipex->envi[ii] + 5, ':');
	i = -1;
	while (paths[++i])
	{
		aux = ft_strjoin(paths[i], "/");
		path = ft_strjoin(aux, pipex->cmdargs[0]);
		free(aux);
		if (access(path, F_OK | X_OK) == 0)
			return (path);
		free(path);
	}
	cleaner_matrix(paths);
	return (NULL);
}