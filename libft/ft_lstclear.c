/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fluzi <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 16:50:39 by fluzi             #+#    #+#             */
/*   Updated: 2024/02/01 16:54:05 by fluzi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*ret;

	if (lst)
	{
		while (*lst)
		{
			ret = (*lst)-> next;
			ft_lstdelone(*lst, del);
			(*lst) = ret;
		}
	}
}
