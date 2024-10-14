/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fluzi <fluzi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 13:45:52 by fluzi             #+#    #+#             */
/*   Updated: 2024/10/14 16:14:10 by fluzi            ###   ########.fr       */
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


void	stampmat(char **mtr)
{
	int	i;

	i = 0;
	while (mtr[i])
	{
		printf("$(red)%s \n", mtr[i]);
		i++;
	}
	printf("\n\n");
}
// Funzione per trovare la variabile PATH dall'ambiente
char	*get_line_path(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (envp[i][0] == 'P' && envp[i][1] == 'A' &&
			envp[i][2] == 'T' && envp[i][3] == 'H' && envp[i][4] == '=')
		{
			printf("PATH trovata: %s\n", envp[i]); 
			return (envp[i]);
		}
		i++;
	}
	return (NULL);
}


// Funzione per trovare il percorso del comando
char	*find_path(char *fun, char **envp)
{
	char	**split_path;
	char	*path;
	char	*p1;
	char	*p2;
	int		i;
	char	**fun_split;

	path = get_line_path(envp);
	if (!path)
	{
		perror("PATH NON TROVATO!");
		exit(EXIT_FAILURE);
	}
	split_path = ft_split(path + 5, ':'); 
	fun_split = ft_split(fun, ' ');
	i = 0;
	stampmat(split_path);
	
	
	while (split_path[i])
	{
		p1 = ft_strjoin(split_path[i], "/");
		p2 = ft_strjoin(p1, fun_split[0]);
		printf("PROVA: %s\n", p2);
		free(p1);
		if (access(p2, X_OK) == 0)
		{
			free_matrix(split_path);
			printf("\n%s\n\n", p2);
			return (p2); 
		}
		free(p2);
		i++;
	}
	free_matrix(split_path); 
	return (NULL); 
}

// Funzione che esegue il comando
void	exe_func(char *argv, char **envp)
{
	char	**matrix_argv;
	char	*path;

	path = find_path(argv, envp);
	if (!path)
	{
		perror("Comando non trovato");
		exit(EXIT_FAILURE);
	}
	matrix_argv = ft_split(argv, ' ');
	if (execve(path, matrix_argv, envp) == -1)
	{
		perror("Errore nell'esecuzione del comando");
		free(path);
		free_matrix(matrix_argv); 
		exit(EXIT_FAILURE);
	}
	free(path); 
	free_matrix(matrix_argv); 
}

// Funzione che gestisce la logica di fork e pipe
void	fork_t(char **argv, int *fd, char **envp, int t)
{
	int	nfd;

	if (t == 0) 
	{
		nfd = open(argv[1], O_RDONLY);
		if (nfd < 0)
		{
			perror("Errore nell'apertura del file di input");
			exit(EXIT_FAILURE);
		}
		dup2(nfd, STDIN_FILENO); 
		dup2(fd[1], STDOUT_FILENO); 
		close(fd[0]);
		close(fd[1]);
		exe_func(argv[2], envp); 
		close(nfd); 
	}
	else 
	{
		nfd = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
		if (nfd < 0)
		{
			perror("Errore nell'apertura del file di output");
			exit(EXIT_FAILURE);
		}
		dup2(fd[0], STDIN_FILENO); 
		dup2(nfd, STDOUT_FILENO); 
		close(fd[0]);
		close(fd[1]);
		exe_func(argv[3], envp); 
		close(nfd); 
	}
}

// Funzione principale
int	main(int argc, char **argv, char **envp)
{
	int		fd[2];
	pid_t	pid;


	if (argc != 5)
	{
		perror("Numero di argomenti non valido");
		exit(EXIT_FAILURE);
	}
	
	if (pipe(fd) == -1)
	{
		perror("Errore nella creazione della pipe");
		exit(EXIT_FAILURE);
	}
	pid = fork(); 
	if (pid < 0)
	{
		perror("Errore nel fork");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0) 
	{
		fork_t(argv, fd, envp, 0);
		exit(EXIT_SUCCESS);
	}
	waitpid(pid, NULL, 0); 
	fork_t(argv, fd, envp, 1); 
	return (0);
}
