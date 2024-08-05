/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hitran <hitran@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 23:54:56 by hitran            #+#    #+#             */
/*   Updated: 2024/08/05 23:22:52 by hitran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include "mylib.h"
# include <fcntl.h>
# include <sys/wait.h>
# include <stdio.h>
# include <errno.h>
# include <string.h>

typedef struct s_pipex
{
	int		argc;
	char	**argv;
	char	**envp;
	int		error;
	int		fd[2];
	int		pipe_id[2];
	int		hd_pipe_id[2];
	int		next_pipe[2];
	pid_t	pid;
}	t_pipex;

//   ALGORITHM    //
void	execute_pipex(t_pipex *pipex);
void	read_here_doc(t_pipex *pipex, int *pipe_id);
char	*find_command_path(char **envp, char **command);
char	**split_command(char *command);

//     UTILS     //
void	create_pipe(int *pipe_id);
void	redirect_fds(int from_fd1, int to_fd1, int from_fd2, int to_fd2);
int		skip_quotes(char *command, int i);
int		skip_word(char *command, int i);

// HANDLE ERRORS //
void	handle_exec_error(char *command_path, char **splitted_command);
void	handle_open_error(char *name, int pipe_num);
void	handle_fork_error(int *fd);
void	handle_read_error(int *fd);

#endif