/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hitran <hitran@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 23:54:56 by hitran            #+#    #+#             */
/*   Updated: 2024/07/11 21:26:44 by hitran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "mylib.h"
# include <fcntl.h>
# include <sys/wait.h>
# include <stdio.h> 

typedef struct s_pipex
{
	int		argc;
	char	**argv;
	char	**envP;
	int		pipe[2];
	int		fd[2];
	pid_t	pid;
}	t_pipex;

// ALGORITHM
void	execute_pipex(t_pipex *pipex);
void	execute_child_process(t_pipex *pipex);
void	execute_parent_process(t_pipex *pipex);
void	excecute_command(t_pipex *pipex, char *command);

// UTILS
char	*find_command_path(t_pipex *pipex, char *command);
char	**split_command(char *command);

#endif //PIPEX
