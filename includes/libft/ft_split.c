/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfortin <kfortin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 14:51:29 by kfortin           #+#    #+#             */
/*   Updated: 2022/04/11 17:18:31 by kfortin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_size_tab(char const *s, char charset)
{
	int	i;
	int	count;
	int	flag;

	i = 0;
	count = 0;
	flag = 0;
	while (s[i])
	{
		if (s[i] == charset)
		{
			flag = 0;
		}
		else if (s[i] != charset && flag == 0)
		{
			flag = 1;
			count++;
		}
		i++;
	}
	return (count);
}

static int	ft_size_word(char const *s, int start, char c)
{
	int	count;

	count = 0;
	while (s[start] != c && s[start])
	{
		if (s[start] == c)
			return (count);
		count++;
		start++;
	}
	return (count);
}

static char	**ft_fct(char const *s, char c, char **tab, int i)
{
	int	j;
	int	k;

	j = 0;
	k = 0;
	while (s[i])
	{
		if (s[i] == c && s[i + 1] != c && j > 0)
		{
			k++;
			j = 0;
		}
		if (s[i] != c)
		{
			if (j == 0)
				tab[k] = ft_calloc((ft_size_word(s, i, c) + 1), sizeof(char));
			tab[k][j] = s[i];
			tab[k][j + 1] = 0;
			j++;
		}
		i++;
	}
	tab[ft_size_tab(s, c)] = NULL;
	return (tab);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	char	**tab;

	i = 0;
	if (!s)
		return (NULL);
	tab = ft_calloc(ft_size_tab(s, c) + 1, sizeof(char *));
	if (!tab)
		return (NULL);
	return (ft_fct(s, c, tab, i));
}
