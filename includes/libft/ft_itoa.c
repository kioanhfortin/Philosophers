/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfortin <kfortin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 09:53:59 by kfortin           #+#    #+#             */
/*   Updated: 2022/04/22 10:25:02 by kfortin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_size_num(int n)
{
	int	count;

	count = 0;
	if (n == 0)
		return (1);
	if (n < 0)
		count++;
	while (n)
	{
		n = n / 10;
		count++;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	long	nb;
	char	*str;
	int		i;
	int		sign;

	nb = n;
	sign = 0;
	i = ft_size_num(nb);
	str = ft_calloc(ft_size_num(nb) + 1, sizeof(char));
	if (!str)
		return (NULL);
	if (nb < 0)
	{
		sign = 1;
		nb = nb * -1;
	}
	str[i] = '\0';
	while (--i >= 0)
	{
		str[i] = nb % 10 + 48;
		nb = nb / 10;
		if (sign == 1 && i == 0)
			str[i] = '-';
	}
	return (str);
}
