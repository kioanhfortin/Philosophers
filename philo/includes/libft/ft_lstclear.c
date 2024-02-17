/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfortin <kfortin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 14:22:48 by kfortin           #+#    #+#             */
/*   Updated: 2022/04/20 12:07:35 by kfortin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*cleanlst;

	while (*lst)
	{
		cleanlst = (*lst)->next;
		ft_lstdelone(*lst, del);
		*lst = cleanlst;
	}
}
