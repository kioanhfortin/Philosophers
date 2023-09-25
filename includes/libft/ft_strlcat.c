/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfortin <kfortin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 14:24:46 by kfortin           #+#    #+#             */
/*   Updated: 2022/04/08 14:04:28 by kfortin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	j;
	size_t	i;
	size_t	dstlen;
	size_t	srclen;

	i = 0;
	j = ft_strlen(dst);
	dstlen = ft_strlen(dst);
	srclen = ft_strlen(src);
	if (dstsize <= 0)
		return (srclen);
	if (dstlen > dstsize)
		return (dstsize + srclen);
	while (src[i] && j < dstsize - 1)
	{
		dst[j++] = src[i++];
	}
	dst[j] = '\0';
	return (dstlen + srclen);
}
