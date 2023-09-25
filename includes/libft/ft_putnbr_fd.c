/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfortin <kfortin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 15:52:00 by kfortin           #+#    #+#             */
/*   Updated: 2022/04/11 17:10:46 by kfortin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	long	nb2;

	nb2 = n;
	if (nb2 < 0)
	{
		nb2 = -nb2;
		ft_putchar_fd('-', fd);
	}
	if (nb2 < 10)
		ft_putchar_fd(nb2 + 48, fd);
	if (nb2 >= 10)
	{
		ft_putnbr_fd(nb2 / 10, fd);
		ft_putnbr_fd(nb2 % 10, fd);
	}
}
