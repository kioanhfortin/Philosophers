/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   die_path_utilis.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfortin <kfortin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 16:59:16 by kfortin           #+#    #+#             */
/*   Updated: 2024/02/20 15:29:07 by kfortin          ###   ########.fr       */
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
	if (time->eat + time->sleep >= time->die)
		return (1);
	return (0);
}

int	ft_finish_eat_then_die(t_time *time)
{
	if (time->eat == time->die)
		return (1);
	return (0);
}

void	nullify(void **ptr)
{
	if (*ptr)
	{
		free(*ptr);
		*ptr = NULL;
	}
}

void	ft_free_all(t_time *time)
{
	nullify((void **)&time->status_fork);
	nullify((void **)&time->status);
	nullify((void **)&time->philo_tid);
	nullify((void **)&time->philo);
	nullify((void **)&time);
}
