/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfortin <kfortin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 14:53:52 by kfortin           #+#    #+#             */
/*   Updated: 2022/04/09 16:27:41 by kfortin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*strjoin;
	size_t	i;
	size_t	j;
	int		len;

	i = -1;
	j = -1;
	if (!s1 || !s2)
		return (NULL);
	len = (ft_strlen(s1) + ft_strlen(s2) + 1);
	strjoin = ft_calloc(len, sizeof(char));
	if (!strjoin)
		return (NULL);
	while (++i < ft_strlen(s1))
		strjoin[i] = s1[i];
	while (++j < ft_strlen(s2))
		strjoin[i + j] = s2[j];
	strjoin[i + j] = '\0';
	return (strjoin);
}
