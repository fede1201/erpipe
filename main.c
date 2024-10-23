/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fluzi <fluzi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 13:45:52 by fluzi             #+#    #+#             */
/*   Updated: 2024/10/23 16:23:10 by fluzi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	exe_func(char *argv, char **envp, int type)
{
	char	**matrix_argv;
	char	*path;

	path = find_path(argv, envp, type);
	if (!path)
		exit(std_error_fail());
	matrix_argv = ft_split(argv, ' ');
	if (execve(path, matrix_argv, envp) == -1)
	{
		perror("Error\n");
		free(path);
		free_matrix(matrix_argv);
		if (type == 0)
			exit(0);
		else
			exit(127);
	}
	free(path);
	free_matrix(matrix_argv);
}

void	fork_baby(char **argv, int *fd, char **envp)
{
	int	nfd;

	if (access(argv[1], R_OK) != 0)
	{
		perror("non permessi");
		exit(0);
	}
	nfd = open(argv[1], O_RDONLY);
	if (nfd < 0)
		exit(std_error_fail());
	dup2(nfd, STDIN_FILENO);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[0]);
	close(fd[1]);
	exe_func(argv[2], envp, 0);
	close(nfd);
}

void	fork_dad(char **argv, int *fd, char **envp)
{
	int	nfd;

	nfd = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (nfd < 0)
		exit(std_error_fail());
	if (access(argv[4], W_OK) != 0)
	{
		perror("non permessi");
		exit(1);
	}
	dup2(fd[0], STDIN_FILENO);
	dup2(nfd, STDOUT_FILENO);
	close(fd[1]);
	exe_func(argv[3], envp, 1);
	close(nfd);
}

int	main(int argc, char **argv, char **envp)
{
	int		fd[2];
	pid_t	pid1;
	pid_t	pid2;
	int		status1;
	int		status2;

	if (argc != 5)
		exit(std_error_fail());
	if (pipe(fd) == -1)
		exit(std_error_fail());
	pid1 = fork();
	if (pid1 < 0)
		exit(std_error_fail());
	else if (pid1 == 0)
	{
		fork_baby(argv, fd, envp);
		exit(1);
	}
	pid2 = fork();
	if (pid2 < 0)
		exit(std_error_fail());
	else if (pid2 == 0)
	{
		fork_dad(argv, fd, envp);
		exit(1);
	}
	close(fd[0]);
	close(fd[1]);
	waitpid(pid1, &status1, 0);
	waitpid(pid2, &status2, 0);
	if (WIFEXITED(status1) && WEXITSTATUS(status1) != 0)
		exit(WEXITSTATUS(status1));
	if (WIFEXITED(status2) && WEXITSTATUS(status2) != 0)
		exit(WEXITSTATUS(status2));
	exit(0);
}
