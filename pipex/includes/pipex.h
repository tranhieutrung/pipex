/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hitran <hitran@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 23:54:56 by hitran            #+#    #+#             */
/*   Updated: 2024/07/11 21:08:03 by hitran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "mylib.h"
// # include <unistd.h> //WRITE, FORK, PIPE, EXECVE
# include <fcntl.h> //OPEN, CLOSE
# include <sys/wait.h> //WAITPID
// # include <stdio.h> //PERROR

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
void	handle_pipe(t_pipex *pipex,);
char	**split_word(char *cmd);
char	*find_path(t_pipex *pipex);

// UTILS
char	*find_command_path(t_pipex *pipex, char *command);
char	**split_command(char *command);

#endif //PIPEX
