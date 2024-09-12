/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fluzi <fluzi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 16:43:29 by fluzi             #+#    #+#             */
/*   Updated: 2024/09/05 15:13:20 by fluzi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	nbstr_len(int n)
{
	int	len;

	len = 0;
	if (n <= 0)
		len++;
	while (n && ++len)
		n /= 10;
	return (len);
}

char	*ft_itoa(int n)
{
	char	*base;
	char	*n_str;
	int		len;

	base = "0123456789";
	len = nbstr_len(n);
	n_str = (char *)malloc(sizeof(char) * len + 1);
	if (n_str == NULL)
		return (NULL);
	n_str[len] = '\0';
	if (n < 0)
		n_str[0] = '-';
	if (n == 0)
		n_str[0] = '0';
	while (n)
	{
		if (n > 0)
			n_str[--len] = base[n % 10];
		else
			n_str[--len] = base[(n % 10) * -1];
		n /= 10;
	}
	return (n_str);
}
