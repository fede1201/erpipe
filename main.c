/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fluzi <fluzi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 13:45:52 by fluzi             #+#    #+#             */
/*   Updated: 2024/09/23 16:50:12 by fluzi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*get_line_path(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (envp[i][0] == 'P' && envp[i][1] == 'A'
		&& envp[i][2] == 'T' && envp[i][3] == 'H' && envp[i][4] == '=')
			return (envp[i]);
		else
			i++;
	}
	return ("Error");
}

char	*find_path(char *fun, char **envp, int i)
{
	char	**split_path;
	char	*path;
	char	*p1;
	char	*p2;

	path = get_line_path(envp);
	if (path[0] != 'P')
		perror("PATH NON TROVATO!");
	split_path = ft_split(path + 5, ':');
	i = 0;
	while (split_path[i])
	{
		p1 = ft_strjoin(split_path[i], "/");
		p2 = ft_strjoin(p1, fun);
		free(p1);
		if (access(p2, X_OK) == 0)
			return (p2);
		else
		{
			free(p2);
			i++;
		}
	}
	return (" ");
}

void	exe_func(char *argv, char **envp)
{
	char	**matrix_argv;
	char	*path;

	path = find_path(argv, envp, 0);
	matrix_argv = ft_split(argv, ' ');
	if (execve(path, matrix_argv, envp) == -1)
		perror("Erroooooor");
}

void	fork_t(char **argv, int *fd, char **envp, int t)
{
	int	nfd;

	if (t == 0)
	{
		nfd = open(argv[1], O_RDONLY, 0777);
		dup2(nfd, STDIN_FILENO);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
		exe_func(argv[2], envp);
	}
	else
	{
		nfd = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
		dup2(fd[0], STDIN_FILENO);
		dup2(nfd, STDOUT_FILENO);
		close(fd[1]);
		exe_func(argv[3], envp);
	}
}

int	main(int argc, char **argv, char **envp)
{
	int		fd[2];
	pid_t	pid;

	if (pipe(fd) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	if (argc < 5 || argc > 5)
		perror("Invalid args");
	else
	{
		pid = fork();
		if (pid < 0)
			perror("Fork fail");
		else if (pid == 0)
		{
			fork_t(argv, fd, envp, 0);
			return (1);
		}
		waitpid(pid, NULL, 0);
		fork_t(argv, fd, envp, 1);
	}
}
