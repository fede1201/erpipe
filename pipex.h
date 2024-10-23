/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fluzi <fluzi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 13:48:17 by fluzi             #+#    #+#             */
/*   Updated: 2024/10/23 14:58:45 by fluzi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <sys/wait.h>
# include "libft/libft.h"

# define RED "\033[31;1m"

char	*find_path(char *fun, char **envp, int type);
char	*path_utils(char *path, char *fun, int i, int type);
int		path_exit(int type);
char	*get_line_path(char **envp);
int		free_matrix(char **matrix);
int		std_error_fail(void);

#endif