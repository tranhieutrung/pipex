/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathfinder.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hitran <hitran@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 23:55:10 by hitran            #+#    #+#             */
/*   Updated: 2024/07/07 23:55:13 by hitran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*pathfinder(t_pipex *pipex)
{
	int		i;
	int		ii;
	char	**paths;
	char	*path;
	char	*aux;

	if (ft_strchr(pipex->cmdargs[0], '/'))
		return (pipex->cmdargs[0]);
	ii = 0;
	while (ft_strncmp(pipex->envi[ii], "PATH=", 5))
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
