/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fluzi <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 17:15:59 by fluzi             #+#    #+#             */
/*   Updated: 2024/02/01 17:17:57 by fluzi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*alloc(char const *s1, char const *s2, char *dst)
{
	size_t	i;
	size_t	y;

	i = 0;
	y = 0;
	while (s1[y])
	{
		dst[i] = s1[y];
		y++;
		i++;
	}
	y = 0;
	while (s2[y])
	{
		dst[i] = s2[y];
		i++;
		y++;
	}
	dst[i] = '\0';
	return (dst);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len1;
	size_t	len2;
	char	*dst;

	if (!s1 || !s2)
		return (NULL);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	dst = (char *) malloc(sizeof(char) * (len1 + len2 + 1));
	if (dst == NULL)
		return (NULL);
	return (alloc(s1, s2, dst));
}
