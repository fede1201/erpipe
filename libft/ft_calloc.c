/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fluzi <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 14:48:29 by fluzi             #+#    #+#             */
/*   Updated: 2024/01/17 15:03:30 by fluzi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	size_t	tot_size;
	void	*dst;

	tot_size = size * count;
	if (count && size && (4294967295 / size <= count))
		return (0);
	dst = malloc (size * count);
	if (dst == NULL)
		return (NULL);
	ft_memset(dst, 0, tot_size);
	return (dst);
}
