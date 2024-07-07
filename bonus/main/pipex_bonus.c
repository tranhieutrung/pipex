#include "pipex_bonus.h"

void	heredoc(t_pipex *pipex, int hd, char *limiter, char **argv)
{
	char	*str_input;
	char	*new_limiter;

	new_limiter = ft_strjoin(limiter, "\n");
	while (1)
	{
		write(1, "> ", 2);
		str_input = get_next_line(STDIN_FILENO);
		if (ft_strncmp(str_input, new_limiter, ft_strlen(str_input)) == 0)
			break ;
		write(hd, str_input, ft_strlen(str_input));
		free(str_input);
	}
	close(hd);
	free(str_input);
	free(new_limiter);
	cmd_controller(pipex, pipex->ac, argv, 2);
}

static int	start_hd(t_pipex *pipex, int argc, char **argv, char **envp)
{
	pipex->path = NULL;
	pipex->cmdargs = NULL;
	pipex->ac = argc;
	pipex->envi = envp;
	pipex->fd[1] = open(argv[argc - 1], O_CREAT | O_RDWR | O_APPEND, 00700);
	if (pipex->fd[0] < 0 || pipex->fd[1] < 0)
		return (1);
	return (0);
}

static int	start_pipex(t_pipex *pipex, int argc, char **argv, char **envp)
{
	pipex->path = NULL;
	pipex->cmdargs = NULL;
	pipex->envi = envp;
	pipex->fd[0] = open(argv[1], O_RDONLY);
	pipex->fd[1] = open(argv[argc - 1], O_CREAT | O_RDWR | O_TRUNC, 00700);
	if (pipex->fd[0] < 0 || pipex->fd[1] < 0)
		return (1);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;
	int		hd[2];

	if (argc < 5)
		return (write(2, ".ERROR: Invalid Number Of Arguments.\n", 37));
	if (ft_strncmp(argv[1], "here_doc", ft_strlen("here_doc")) == 0)
	{
		if (argc < 6)
			return (write(2, ".ERROR: argc != 6.\n", 19));
		if (start_hd(&pipex, argc, argv, envp) != 0)
			return (write(2, ".ERROR: start_heredoc.\n", 22));
		pipe(hd);
		pipex.fd[0] = hd[0];
		heredoc(&pipex, hd[1], argv[2], argv);
	}
	else
	{
		if (start_pipex(&pipex, argc, argv, envp) != 0)
			return (write(2, ".ERROR: start_pipex.\n", 20));
		cmd_controller(&pipex, argc, argv, 1);
	}
	return (0);
}
