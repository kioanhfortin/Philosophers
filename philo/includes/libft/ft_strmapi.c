/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfortin <kfortin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 16:04:20 by kfortin           #+#    #+#             */
/*   Updated: 2022/04/11 17:21:07 by kfortin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int		i;
	char	*str;
	char	*strmapi;

	i = 0;
	str = (char *)s;
	if (!s)
		return (NULL);
	strmapi = ft_calloc(ft_strlen(str) + 1, sizeof(char));
	if (!strmapi)
		return (NULL);
	while (str[i])
	{
		strmapi[i] = f(i, str[i]);
		i++;
	}
	return (strmapi);
}
