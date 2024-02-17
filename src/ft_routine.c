/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_routine.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfortin <kfortin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 13:12:11 by kfortin           #+#    #+#             */
/*   Updated: 2024/02/17 16:12:34 by kfortin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*ft_routine_die_thinking(t_philo *philo)
{
	if (philo->id % 2 == 0)
		ft_usleep(philo->time->eat, philo);
	go_print(philo, THINK, philo->id);
	ft_philo_eat(philo);
	ft_usleep(philo->time->eat, philo);
	pthread_mutex_unlock(&philo->fork_mutex_right);
	pthread_mutex_unlock(philo->fork_mutex_left);
	if (ft_check_cycle(philo) == 1)
	{
		pthread_exit(philo->time->philo_tid[philo->id]);
	}
	go_print(philo, SLEEP, philo->id);
	ft_usleep(philo->time->sleep, philo);
	if (ft_get_time(philo) < philo->time->die)
	{
		ft_usleep(philo->time->die - ft_get_time(philo), philo);
	}
	go_print(philo, DIE, philo->id);
	pthread_exit(philo->time->philo_tid[philo->id]);
}

void	*ft_routine_die_sleeping(t_philo *philo)
{
	if (philo->id % 2 == 0)
		ft_usleep(philo->time->eat / 2, philo);
	while (1)
	{
		go_print(philo, THINK, philo->id);
		ft_philo_eat(philo);
		ft_usleep(philo->time->eat, philo);
		pthread_mutex_unlock(&philo->fork_mutex_right);
		pthread_mutex_unlock(philo->fork_mutex_left);
		if (ft_check_cycle(philo) == 1)
			pthread_exit(philo->time->philo_tid[philo->id]);
		if ((philo->time->sleep < philo->time->die)
			&& (ft_get_time(philo) >= philo->time->die + philo->time->eat))
		{
			go_print(philo, DIE, philo->id);
			pthread_exit(philo->time->philo_tid[philo->id]);
		}
		else if (ft_get_time(philo) >= philo->time->die)
		{
			go_print(philo, DIE, philo->id);
			pthread_exit(philo->time->philo_tid[philo->id]);
		}
		go_print(philo, SLEEP, philo->id);
		ft_usleep(philo->time->sleep, philo);
	}
}

void	*ft_routine_die_eating(t_philo *philo)
{
	if (philo->id % 2 == 0)
		ft_usleep(philo->time->eat, philo);
	if (ft_check_cycle(philo) == 1)
		pthread_exit(philo->time->philo_tid[philo->id]);
	go_print(philo, THINK, philo->id);
	ft_philo_eat(philo);
	ft_usleep(philo->time->die, philo);
	pthread_mutex_unlock(&philo->fork_mutex_right);
	pthread_mutex_unlock(philo->fork_mutex_left);
	go_print(philo, DIE, 2);
	pthread_exit(philo->time->philo_tid[philo->id]);
}

void	*ft_routine_alone(t_philo *philo)
{
	pthread_mutex_lock(&philo->fork_mutex_right);
	go_print(philo, FORK, philo->id);
	ft_usleep(philo->time->die, philo);
	go_print(philo, DIE, philo->id);
	pthread_exit(philo->time->philo_tid[philo->id]);
}

void	*ft_routine_principale(t_philo *philo)
{
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
		pthread_mutex_unlock(&philo->fork_mutex_right);
		pthread_mutex_unlock(philo->fork_mutex_left);
		go_print(philo, SLEEP, philo->id);
		ft_usleep(philo->time->sleep, philo);
	}
	pthread_exit(philo->time->philo_tid[philo->id]);
}
