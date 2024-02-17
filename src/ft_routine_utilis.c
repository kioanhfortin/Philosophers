/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_routine_utilis.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfortin <kfortin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 16:55:18 by kfortin           #+#    #+#             */
/*   Updated: 2024/02/16 19:06:03 by kfortin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_check_status(t_philo *philo)
{
	int	i;

	i = 0;
	if (philo->time->stop == 1)
		return (1);
	while (i < philo->time->nbr_philo)
	{
		pthread_mutex_lock(&philo->time->status_mutex);
		if (philo->time->status[i] == 1)
		{
			philo->time->stop = 1;
			return (1);
		}
		pthread_mutex_unlock(&philo->time->status_mutex);
		i++;
	}
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
		if (i == CYCLE)
			printf("All philo have eat");
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
		if (philo->time->nbr_cycle == philo->cycle_count)
			return (1);
	}
	philo->cycle_count++;
	return (0);
}

void	*ft_routine_eat_then_die(t_philo *philo)
{
	// printf("5 -- eat then die\n");
	if (philo->id % 2 == 0)
		ft_usleep(philo->time->eat / 2, philo);
	while (1)
	{
		go_print(philo, THINK, philo->id);
		ft_philo_eat(philo);
		ft_usleep(philo->time->eat, philo);
		pthread_mutex_unlock(&philo->fork.fork_mutex_right);
		pthread_mutex_unlock(philo->fork.fork_mutex_left);
		if (ft_get_time(philo) >= philo->time->die)
		{
			go_print(philo, DIE, philo->id);
			pthread_exit(philo->time->philo_tid[philo->id]);
		}
		go_print(philo, SLEEP, philo->id);
		ft_usleep(philo->time->sleep, philo);
	}
}

void	*ft_routine_live_odd(t_philo *philo)
{
	// printf("3 -- live odd\n");
	while (1)
	{
		if (philo->id % 2 == 0)
			ft_usleep(philo->time->eat, philo);
		go_print(philo, THINK, philo->id);
		if (ft_check_cycle(philo) == 1)
		{
			break ;
		}
		ft_philo_eat(philo);
		ft_usleep(philo->time->eat, philo);
		pthread_mutex_unlock(&philo->fork.fork_mutex_right);
		pthread_mutex_unlock(philo->fork.fork_mutex_left);
		go_print(philo, SLEEP, philo->id);
		ft_usleep(philo->time->sleep, philo);
	}
	pthread_exit(philo->time->philo_tid[philo->id]);
}
