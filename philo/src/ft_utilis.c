/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utilis.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfortin <kfortin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 15:25:24 by kfortin           #+#    #+#             */
/*   Updated: 2024/02/17 16:40:27 by kfortin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_nb_even(int nb)
{
	if (nb % 2 == 0)
		return (1);
	return (0);
}

void	ft_usleep(long tim, t_philo *philo)
{
	long long	start;

	start = ft_get_time(philo);
	usleep(1000);
	while (ft_get_time(philo) < tim + start)
		usleep(150);
}

int	ft_init_philo(t_time *time, t_philo *philo)
{
	int	i;

	i = 0;
	philo = ft_calloc(sizeof(struct s_philo), time->nbr_philo);
	if (!philo)
		return (1);
	time->philo_tid = ft_calloc(sizeof(pthread_t), time->nbr_philo);
	if (!time->philo_tid)
		return (1);
	time->philo = philo;
	while (i < time->nbr_philo)
	{
		philo[i].time = time;
		philo[i].id = i + 1;
		i++;
	}
	if (ft_calloc_struct(time) == 1)
		return (1);
	ft_is_philo_die(time);
	if (ft_init_thread(time, philo) != 0)
		return (1);
	return (0);
}

int	ft_calloc_struct(t_time *time)
{
	time->status = ft_calloc(sizeof(int *), time->nbr_philo);
	if (!time->status)
		return (1);
	time->status_fork = ft_calloc(sizeof(int *), time->nbr_philo);
	if (!time->status_fork)
		return (1);
	return (0);
}
