/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hitran <hitran@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 21:18:34 by hitran            #+#    #+#             */
/*   Updated: 2024/07/13 22:36:34 by hitran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;

	if (argc != 5)
	{
		ft_printf_fd(2, "pipex: invalid number of arguments.\n");
		return (1);
	}
	pipex.argc = argc;
	pipex.argv = argv;
	pipex.envp = envp;
	pipex.error = 0;
	if (pipe(pipex.pipe) == -1)
	{
		perror("pipex: pipe\n");
		exit (1);
	}
	execute_pipex(&pipex);
	exit ((pipex.error >> 8) & 255);
}
