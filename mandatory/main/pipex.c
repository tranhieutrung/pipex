/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hitran <hitran@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 23:54:26 by hitran            #+#    #+#             */
/*   Updated: 2024/07/08 08:50:01 by hitran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **env_pt)
{
	t_pipex	pipex;

	if (argc != 5)
		return (write(2, ".ERROR: Invalid Number Of Arguments.\n", 37));
	pipex.path = NULL;
	pipex.cmdargs = NULL;
	pipex.envi = env_pt;
	pipex.fd[0] = open(argv[1], O_RDONLY);
	pipex.fd[1] = open(argv[4], O_CREAT | O_RDWR | O_TRUNC, 00700);
	if (pipex.fd[0] < 0 || pipex.fd[1] < 0)
		return (write(2, ".ERROR: start_pipex.\n", 20));
	handle_pipe(&pipex, argv);
	return (0);
}
