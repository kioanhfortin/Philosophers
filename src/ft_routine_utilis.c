/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_routine_utilis.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfortin <kfortin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 16:55:18 by kfortin           #+#    #+#             */
/*   Updated: 2024/02/13 18:00:37 by kfortin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_check_status(t_philo *philo)
{
	int	i;

	i = 0;
	if (philo->time->stop == 1)
		return (1);
	pthread_mutex_lock(&philo->time->status_mutex);
	while (i < philo->time->nbr_philo)
	{
		if (philo->time->status[i] == 1)
		{
			philo->time->stop = 1;
			return (1);
		}
		i++;
	}
	pthread_mutex_unlock(&philo->time->status_mutex);
	return (0);
}

void	go_print(t_philo *philo, int i, int philo_nb)
{
	pthread_mutex_lock(&philo->time->stop_mutex);
	if (ft_check_status(philo) == 0)
	{
		pthread_mutex_lock(&philo->time->print_mutex);
		if (i == FORK)
			printf("%zu %d has taken a fork\n", ft_get_time(philo), philo_nb);
		if (i == EAT)
			printf("%zu %d is eating\n", ft_get_time(philo), philo_nb);
		if (i == SLEEP)
			printf("%zu %d is sleeping\n", ft_get_time(philo), philo_nb);
		if (i == THINK)
			printf("%zu %d is thinking\n", ft_get_time(philo), philo_nb);
		if (i == DIE)
		{
			printf("%zu %d died\n", ft_get_time(philo), philo_nb);
			pthread_mutex_lock(&philo->time->status_mutex);
			philo->time->status[philo->id - 1] = 1;
			pthread_mutex_unlock(&philo->time->status_mutex);
		}
		pthread_mutex_unlock(&philo->time->print_mutex);
	}
	pthread_mutex_unlock(&philo->time->stop_mutex);
}

int	ft_check_cycle(t_philo *philo)
{
	if (philo->time->nbr_cycle != 0)
	{
		pthread_mutex_lock(&philo->time->cycle_mutex);
		if (philo->time->nbr_cycle == philo->time->cycle_count)
		{
			pthread_mutex_unlock(&philo->time->cycle_mutex);
			return (1);
		}
		pthread_mutex_unlock(&philo->time->cycle_mutex);
	}
	pthread_mutex_lock(&philo->time->cycle_mutex);
	philo->time->cycle_count++;
	pthread_mutex_unlock(&philo->time->cycle_mutex);
	return (0);
}

void	*ft_routine_eat_then_die(t_philo *philo)
{
	pthread_exit(philo->time->philo_tid[philo->id]);
}
