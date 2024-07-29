/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hitran <hitran@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 21:18:34 by hitran            #+#    #+#             */
/*   Updated: 2024/07/29 12:04:10 by hitran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;

	if (argc < 5)
	{
		ft_printf_fd(2, "pipex: invalid number of arguments.\n");
		exit (1);
	}
	pipex.argc = argc;
	pipex.argv = argv;
	pipex.envp = envp;
	pipex.error = 0;
	execute_pipex(&pipex);
	exit ((pipex.error >> 8) & 255);
}
