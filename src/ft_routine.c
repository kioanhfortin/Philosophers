/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_routine.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfortin <kfortin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 13:12:11 by kfortin           #+#    #+#             */
/*   Updated: 2024/02/14 22:26:56 by kfortin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*ft_routine_die_thinking(t_philo *philo)
{
	// printf("2 -- die thinking even\n");
	if (philo->id % 2 == 0)
		ft_usleep(philo->time->eat, philo);
	ft_philo_think(philo);
	ft_philo_eat(philo);
	ft_usleep(philo->time->eat, philo);
	pthread_mutex_unlock(&philo->fork.fork_mutex_right);
	pthread_mutex_unlock(philo->fork.fork_mutex_left);
	if (ft_check_cycle(philo) == 1)
	{
		// printf("in\n");
		pthread_exit(philo->time->philo_tid[philo->id]);
	}
	go_print(philo, SLEEP, philo->id);
	if (ft_get_time(philo) < philo->time->die)
	{
		ft_usleep(philo->time->die - ft_get_time(philo), philo);
	}
	go_print(philo, DIE, philo->id);
	pthread_exit(philo->time->philo_tid[philo->id]);
}

void	*ft_routine_die_sleeping(t_philo *philo)
{
	// printf("4 -- die sleeping\n");
	if (philo->id % 2 == 0)
		ft_usleep(philo->time->eat, philo);
	// ft_philo_think(philo);
	go_print(philo, THINK, philo->id);
	ft_philo_eat(philo);
	ft_usleep(philo->time->eat, philo);
	pthread_mutex_unlock(&philo->fork.fork_mutex_right);
	pthread_mutex_unlock(philo->fork.fork_mutex_left);
	if (ft_check_cycle(philo) == 1)
		pthread_exit(philo->time->philo_tid[philo->id]);
	go_print(philo, SLEEP, philo->id);
	ft_usleep(philo->time->sleep, philo);
	go_print(philo, DIE, philo->id);
	pthread_exit(philo->time->philo_tid[philo->id]);
}

void	*ft_routine_die_eating(t_philo *philo)
{
	// printf("1 -- die eating\n");
	if (ft_check_cycle(philo) == 1)
		pthread_exit(philo->time->philo_tid[philo->id]);
	ft_philo_eat(philo);
	ft_usleep(philo->time->die, philo);
	pthread_mutex_unlock(&philo->fork.fork_mutex_right);
	pthread_mutex_unlock(philo->fork.fork_mutex_left);
	go_print(philo, DIE, 2);
	pthread_exit(philo->time->philo_tid[philo->id]);
}

void	*ft_routine_alone(t_philo *philo)
{
	// printf("0 -- die alone\n");
	pthread_mutex_lock(&philo->fork.fork_mutex_right);
	go_print(philo, FORK, philo->id);
	ft_usleep(philo->time->die, philo);
	go_print(philo, DIE, philo->id);
	pthread_exit(philo->time->philo_tid[philo->id]);
}

void	*ft_routine_principale(t_philo *philo)
{
	// printf("6 -- never die\n");
	if (philo->id % 2 == 0)
		ft_usleep(philo->time->eat, philo);
	while (1)
	{
		if (ft_check_cycle(philo) == 1)
		{
			break ;
		}
		go_print(philo, THINK, philo->id);
		ft_philo_eat(philo);
		ft_usleep(philo->time->eat, philo);
		pthread_mutex_unlock(&philo->fork.fork_mutex_right);
		pthread_mutex_unlock(philo->fork.fork_mutex_left);
		go_print(philo, SLEEP, philo->id);
		ft_usleep(philo->time->sleep, philo);
	}
	pthread_exit(philo->time->philo_tid[philo->id]);
}
