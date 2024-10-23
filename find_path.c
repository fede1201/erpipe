/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fluzi <fluzi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 15:25:58 by fluzi             #+#    #+#             */
/*   Updated: 2024/10/23 14:58:27 by fluzi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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

int	path_exit(int type)
{
	if (type == 1)
		return (127);
	return (0);
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
	exit(path_exit(type));
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
