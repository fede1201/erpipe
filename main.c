/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fluzi <fluzi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 13:45:52 by fluzi             #+#    #+#             */
/*   Updated: 2024/09/12 15:30:08 by fluzi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "pipex.h"

char *find_path(char *fun, char **envp)
{
	char	**split_path;
	char	*path;
	int 	i;
	char	*p1;
	char	*p2;
	
	while (envp[i])
	{
		if (envp[i][0] == 'P' && envp[i][1] == 'A' && envp[i][2] == 'T' 
			&& envp[i][3] == 'H' && envp[i][4] == '=' )
			break;
		else
			i++;
	}
	if (envp[i][0] != 'P')
		perror("PATH NON TROVATO!");
	split_path = ft_split(envp[i][5], ':');
	i = 0;
	while (split_path[i])
	{
		p1 = ft_strjoin(split_path[i], '/');
		p2 = ft_strjoin(p1, fun);
		free(p1);
		if (access(p2,X_OK))
			return (p2);
		else 
		{
			free(p2);
			i++;
		}
	}
	perror("Function not found");
}

int	exe_func(char **argv, char **envp)
{
	
}

void	baby_fork(char **argv, int *fd, char **envp)
{
	int nfd;
	
	nfd = open(argv[1], O_RDONLY, 0777);
	dup2(STDIN_FILENO, nfd);
	dup2(STDOUT_FILENO, fd[1]);
	exe_func(argv, envp);
}

int main(int argc, char **argv, char **envp)
{
	int		fd[2];
	pid_t	pid;
	
	if (pipe(fd) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	if (argv != 5)
		perror("Invalid args");
	else 
	{
		pid = fork();
		if (pid < 0)
  			perror("Fork fail");
		else if (pid == 0)
		{
			baby_fork(argv, fd, envp);
  		}
		else
		{
			/* processo padre.
			* la variabile pid contiene il pid del processo figlio
			*/
 		}
	}
}

if (envp[i][0] == 'P' && envp[i][1] == 'A' && envp[i][2] == 'T' && envp[i][3] == 'H' && envp[i][4] == '=' )