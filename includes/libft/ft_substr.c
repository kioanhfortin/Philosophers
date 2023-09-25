/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfortin <kfortin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 13:21:51 by kfortin           #+#    #+#             */
/*   Updated: 2022/04/20 11:43:14 by kfortin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	j;
	char	*str;
	char	*substr;

	i = 0;
	j = 0;
	str = (char *)s;
	if (!str)
		return (NULL);
	if (len > ft_strlen((char *)s))
		len = ft_strlen((char *)s);
	substr = ft_calloc(len + 1, sizeof(char));
	if (!substr)
		return (NULL);
	if (start >= ft_strlen(str))
		return (substr);
	while (str[i] && i < len)
	{
		substr[j] = str[start + i];
		j++;
		i++;
	}
	return (substr);
}
