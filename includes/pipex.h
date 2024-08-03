/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hitran <hitran@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 23:54:56 by hitran            #+#    #+#             */
/*   Updated: 2024/08/03 23:17:55 by hitran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

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

void	execute_pipex(t_pipex *pipex);
void	read_here_doc(t_pipex *pipex, int *pipe_id);
char	*find_command_path(char **envp, char **command);
char	**split_command(char *command);
int		skip_quotes(char *command, int i);
int		skip_word(char *command, int i);
void	check_quote(int argc, char **argv);
int		is_all_white_space(char *s);
void	create_pipe(int *pipe_id);
void	redirect_fds(int from_fd1, int to_fd1, int from_fd2, int to_fd2);
void	handle_exec_error(char *command_path, char **splitted_command);
void	handle_empty_command(char *trimmed_command, char *command);
void	handle_open_error(char *name, int pipe_num);
void	handle_fork_error(int *fd);
void	handle_read_error(int *fd);

#endif