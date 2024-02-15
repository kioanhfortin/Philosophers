/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utilis_thread.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfortin <kfortin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 05:25:56 by kfortin           #+#    #+#             */
/*   Updated: 2024/02/14 22:27:18 by kfortin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

time_t	ft_get_time(t_philo *philo)
{
	struct timeval	end;

	gettimeofday(&end, NULL);
	return ((end.tv_sec - philo->time->start.tv_sec) * 1000 + (end.tv_usec
			- philo->time->start.tv_usec) / 1000);
}

void	ft_philo_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->fork.fork_mutex_right);
	pthread_mutex_lock(philo->fork.fork_mutex_left);
	pthread_mutex_lock(&philo->time->status_fork_mutex);
	if (philo->id != 0)
		philo->time->status_fork[philo->id - 1] = 1;
	else
		philo->time->status_fork[philo->time->nbr_philo] = 1;
	pthread_mutex_unlock(&philo->time->status_fork_mutex);
	go_print(philo, FORK, philo->id);
	go_print(philo, FORK, philo->id);
	go_print(philo, EAT, philo->id);
	pthread_mutex_lock(&philo->time->last_diner_mutex);
	philo->time->tmp_last_diner = ft_get_time(philo);
	pthread_mutex_unlock(&philo->time->last_diner_mutex);
}

int	ft_check_status_fork(t_philo *philo)
{
	pthread_mutex_lock(&philo->time->status_fork_mutex);
	if (philo->time->status_fork[philo->id] == 1 || (philo->id != 1
			&& philo->time->status_fork[philo->id - 1] == 1) || (philo->id == 1
			&& philo->time->status_fork[philo->time->nbr_cycle] == 1))
	{
		if (philo->id != 0)
			philo->time->status_fork[philo->id - 1] = 0;
		else
			philo->time->status_fork[philo->time->nbr_philo] = 0;
		pthread_mutex_unlock(&philo->time->status_fork_mutex);
		return (0);
	}
	else
	{
		pthread_mutex_unlock(&philo->time->status_fork_mutex);
		return (1);
	}
}

void	ft_philo_think(t_philo *philo)
{
	if (ft_check_status_fork(philo) == 0)
	{
		go_print(philo, THINK, philo->id);
		ft_usleep(philo->time->eat, philo);
	}
}

// void	ft_philo_die(t_philo *philo)
// {
// 	// time_t time_elapsed;
// 	// time_elapsed = ft_get_time(philo) - philo->time->tmp_last_diner;
// 	// if (time_elapsed > philo->time->die)
// 	// {
// 	pthread_mutex_lock(&philo->time->print_mutex);
// 	printf("%zu %d died\n", ft_get_time(philo), philo->id);
// 	pthread_mutex_unlock(&philo->time->print_mutex);
// 	// philo->status = 1;
// 	// }
// }