/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   die_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfortin <kfortin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 14:01:28 by kfortin           #+#    #+#             */
/*   Updated: 2024/02/17 16:08:45 by kfortin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_time_eat_die_even(t_time *time)
{
	if (time->eat > time->sleep && time->nbr_philo % 2 == 0)
	{
		if (time->die * 2 >= time->eat)
			return (1);
		else if (time->die * 2 < time->eat)
			return (0);
	}
	return (0);
}

int	ft_time_eat_die_odd(t_time *time)
{
	if (time->eat > time->sleep && time->nbr_philo % 2 == 0)
	{
		if (time->die * 2 >= time->eat)
			return (0);
		else if (time->die * 2 < time->eat)
			return (1);
	}
	return (0);
}

void	ft_is_philo_die(t_time *time)
{
	int	count;
	int	(*built_tab[6])(t_time *);

	count = 1;
	built_tab[1] = ft_die_eating;
	built_tab[2] = ft_time_eat_die_even;
	built_tab[3] = ft_time_eat_die_odd;
	built_tab[4] = ft_die_sleeping;
	built_tab[5] = ft_finish_eat_then_die;
	while (count < 6)
	{
		if ((built_tab[count])(time) == 1)
			break ;
		count++;
	}
	if (time->nbr_philo == 1)
		time->way_to_die = ONE_PHILO;
	else
		time->way_to_die = count;
}
