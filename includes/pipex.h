/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hitran <hitran@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 23:54:56 by hitran            #+#    #+#             */
/*   Updated: 2024/07/08 08:59:53 by hitran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "mylib.h"
// # include <unistd.h> //WRITE, FORK, PIPE, EXECVE
// # include <stdlib.h> //MALLOC, NULL
# include <fcntl.h> //OPEN, CLOSE
# include <sys/wait.h> //WAITPID
# include <stdio.h> //PERROR

typedef struct s_pipex
{
	pid_t	pid;
	int		pipe[2];
	int		fd[2];
	char	*path;
	char	**cmdargs;
	char	**envi;
}	t_pipex;

//----------PIPEX----------//
void	handle_pipe(t_pipex *pipex, char **argv);
char	**split_word(char *cmd);
char	*find_path(t_pipex *pipex);

//----------QUOTE----------//
int		verify_quote(char *cmd, int i);
int		is_quote(char *cmd, int i);
char	*remove_quote(char *trim, char quote);

#endif //PIPEX
