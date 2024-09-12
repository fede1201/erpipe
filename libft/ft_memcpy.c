/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fluzi <fluzi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 14:25:44 by fluzi             #+#    #+#             */
/*   Updated: 2024/09/05 16:28:56 by fluzi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*t;

	t = (void *)dst;
	i = 0;
	while (i < n)
	{
		*(unsigned char *) dst++ = *(unsigned char *) src++;
		i++;
	}
	return (t);
}
