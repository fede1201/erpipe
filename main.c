/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fluzi <fluzi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 13:45:52 by fluzi             #+#    #+#             */
/*   Updated: 2024/10/17 17:51:31 by fluzi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	free_matrix(char **matrix)
{
	int	y;

	y = 0;
	while (matrix[y] != NULL)
	{
		free(matrix[y]);
		y++;
	}
	free(matrix);
	return (1);
}

char	*get_line_path(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (envp[i][0] == 'P' && envp[i][1] == 'A' &&
			envp[i][2] == 'T' && envp[i][3] == 'H' && envp[i][4] == '=')
			return (envp[i]);
		i++;
	}
	exit(1);
}

char	*path_utils(char *path, char *fun, int i, int type)
{
	char	*p1;
	char	*p2;
	char	**fun_split;
	char	**split_path;

	split_path = ft_split(path + 5, ':');
	fun_split = ft_split(fun, ' ');
	i = 0;
	while (split_path[i])
	{
		p1 = ft_strjoin(split_path[i], "/");
		p2 = ft_strjoin(p1, fun_split[0]);
		free(p1);
		if (access(p2, X_OK) == 0)
		{
			free(fun_split);
			free_matrix(split_path);
			return (p2);
		}
		free(p2);
		i++;
	}
	free(fun_split);
	free_matrix(split_path);
	if (type == 1)
		exit(127);
	exit(0);
}

char	*find_path(char *fun, char **envp, int type)
{
	char	*path;

	path = get_line_path(envp);
	if (!path)
	{
		perror("Error \n");
		exit(0);
	}
	return (path_utils(path, fun, 0, type));
}

void	exe_func(char *argv, char **envp, int type)
{
	char	**matrix_argv;
	char	*path;

	path = find_path(argv, envp, type);
	if (!path)
	{
		perror("Command not found\n");
		exit(0);
	}
	matrix_argv = ft_split(argv, ' ');
	if (execve(path, matrix_argv, envp) == -1)
	{
		perror("Error \n");
		free(path);
		free_matrix(matrix_argv);
		if (type == 0)
			exit(0);
		exit(127);
	}
	free(path);
	free_matrix(matrix_argv);
}

void	fork_t(char **argv, int *fd, char **envp, int t)
{
	int	nfd;

	if (t == 0)
	{
		nfd = open(argv[1], O_RDONLY);
		if (nfd < 0)
		{
			printf("%d", nfd);
			perror("Error \n");
			exit(EXIT_SUCCESS);
		}
			dup2(nfd, STDIN_FILENO);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
		close(fd[1]);
		exe_func(argv[2], envp, 0);
		close(nfd);
	}
	else
	{
		nfd = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
		if (nfd < 0)
		{
			perror("Error \n");
			exit(EXIT_FAILURE);
		}
		dup2(fd[0], STDIN_FILENO);
		dup2(nfd, STDOUT_FILENO);
		close(fd[1]);
		exe_func(argv[3], envp, 1);
		close(nfd);
	}
}

int	main(int argc, char **argv, char **envp)
{
	int		fd[2];
	pid_t	pid1, pid2;
	int		status1, status2;

	if (argc != 5)
	{
		perror("Error \n");
		exit(EXIT_FAILURE);
	}
	if (pipe(fd) == -1)
	{
		perror("Error \n");
		exit(EXIT_FAILURE);
	}
	pid1 = fork();
	if (pid1 < 0)
	{
		perror("Error \n");
		exit(EXIT_FAILURE);
	}
	else if (pid1 == 0)
	{
		fork_t(argv, fd, envp, 0);
		exit(1);
	}
	pid2 = fork();
	if (pid2 < 0)
	{
		perror("Error \n");
		exit(EXIT_FAILURE);
	}
	else if (pid2 == 0)
	{
		fork_t(argv, fd, envp, 1);
		exit(1);
	}
	close(fd[0]);
	close(fd[1]);
	waitpid(pid1, &status1, 0);
	waitpid(pid2, &status2, 0);

	if (WIFEXITED(status2))
    	return WEXITSTATUS(status2);
	return (0);
}
