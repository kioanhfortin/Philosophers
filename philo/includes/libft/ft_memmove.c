/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfortin <kfortin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 15:13:52 by kfortin           #+#    #+#             */
/*   Updated: 2022/04/11 16:43:24 by kfortin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	void	*temp;
	size_t	i;

	i = 0;
	if (!dst && !src)
		return (NULL);
	temp = ft_calloc(len, sizeof(char));
	while (i < len)
	{
		((char *)temp)[i] = ((char *)src)[i];
		i++;
	}
	i = 0;
	while (i < len)
	{
		((char *)dst)[i] = ((char *)temp)[i];
		i++;
	}
	free (temp);
	return (dst);
}
