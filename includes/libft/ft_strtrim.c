/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfortin <kfortin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 16:14:08 by kfortin           #+#    #+#             */
/*   Updated: 2022/04/21 11:16:56 by kfortin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_ischarset(char c, char const *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

static int	ft_sizestr(char const *s1, char const *set)
{
	int	i;
	int	trimcount;
	int	len;

	i = 0;
	trimcount = 0;
	len = ft_strlen(s1);
	while (s1[i++] && ft_ischarset(s1[i], set) == 1)
		trimcount++;
	i = len;
	while (i-- > 0 && ft_ischarset(s1[i], set) == 1)
		trimcount++;
	return (len - trimcount);
}

static int	ft_end(char const *s1, char const *set)
{
	int	i;
	int	end;

	i = ft_strlen(s1);
	end = 0;
	while (i-- > 0 && ft_ischarset(s1[i], set) == 1)
		end++;
	return (ft_strlen(s1) - end);
}

static char	*ft_fct(char const *s1, char const *set, char *strtrim)
{
	int	i;
	int	j;
	int	flag;

	i = 0;
	j = 0;
	flag = 0;
	while (s1[i])
	{
		if (ft_ischarset(s1[i], set) && flag == 1 && i < ft_end(s1, set))
		{
			strtrim[j++] = s1[i];
		}
		else if (!(ft_ischarset(s1[i], set)) && i < ft_end(s1, set))
		{
			flag = 1;
			strtrim[j++] = s1[i];
		}
		i++;
	}
	strtrim[j] = '\0';
	return (strtrim);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*strtrim;

	if (!s1 || !set)
		return (NULL);
	if (ft_sizestr(s1, set) <= 0)
		return (ft_strdup(""));
	strtrim = ft_calloc(ft_sizestr(s1, set) + 1, sizeof(char));
	if (!strtrim)
		return (NULL);
	return (ft_fct(s1, set, strtrim));
}
