/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   die_path_utilis.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfortin <kfortin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 16:59:16 by kfortin           #+#    #+#             */
/*   Updated: 2024/02/14 22:25:47 by kfortin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_die_eating(t_time *time)
{
	if (time->eat > time->die)
		return (1);
	return (0);
}

int	ft_die_sleeping(t_time *time)
{
	if ((time->eat + time->sleep == time->die) || (time->sleep >= time->eat))
	// if ((time->eat + time->sleep == time->die))
		return (1);
	return (0);
}

int	ft_finish_eat_then_die(t_time *time)
{
	if (time->eat == time->die)
		return (1);
	return (0);
}
