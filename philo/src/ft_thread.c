/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_thread.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfortin <kfortin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 14:38:32 by kfortin           #+#    #+#             */
/*   Updated: 2024/02/20 15:46:41 by kfortin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_init_mutex(t_time *time)
{
	if (pthread_mutex_init(&time->print_mutex, NULL) != 0)
		return (printf("error mutex initialization\n"), 1);
	if (pthread_mutex_init(&time->last_diner_mutex, NULL) != 0)
		return (printf("error mutex initialization\n"), 1);
	if (pthread_mutex_init(&time->status_mutex, NULL) != 0)
		return (printf("error mutex initialization\n"), 1);
	if (pthread_mutex_init(&time->status_fork_mutex, NULL) != 0)
		return (printf("error mutex initialization\n"), 1);
	if (pthread_mutex_init(&time->stop_mutex, NULL) != 0)
		return (printf("error mutex initialization\n"), 1);
	if (pthread_mutex_init(&time->cycle_mutex, NULL) != 0)
		return (printf("error mutex initialization\n"), 1);
	return (0);
}

int	ft_init_mutex_struct(t_time *time, t_philo *philo)
{
	int	i;

	i = 0;
	if (ft_init_mutex(time) == 1)
		return (1);
	while (i < time->nbr_philo)
	{
		if (pthread_mutex_init(&philo[i].fork_mutex_right, NULL) != 0)
			return (printf("error mutex initialization\n"), 1);
		i++;
	}
	i = 0;
	while (i < time->nbr_philo)
	{
		if (i > 0)
			philo[i].fork_mutex_left = &philo[i - 1].fork_mutex_right;
		else if (philo->time->nbr_philo != 1)
			philo[i].fork_mutex_left = &philo[time->nbr_philo
				- 1].fork_mutex_right;
		i++;
	}
	return (0);
}

int	ft_init_thread(t_time *time, t_philo *philo)
{
	int	i;

	i = 0;
	if (gettimeofday(&philo->time->start, NULL) == -1)
		return (printf("error time"), -1);
	if (ft_init_mutex_struct(time, philo) != 0)
		return (1);
	while (i < time->nbr_philo)
	{
		if (ft_find_philo(time, philo, i) != 0)
			return (1);
		i++;
	}
	ft_join_and_destroy(time, philo);
	if (time->way_to_die == 6 || time->way_to_die == 3)
		go_print(philo, CYCLE, philo->id);
	return (0);
}

int	ft_norme_philo(t_time *time, t_philo *philo, int res, int i)
{
	if (philo->time->way_to_die == EAT_DIE_ODD)
		res = pthread_create(&time->philo_tid[i], NULL,
				(void *)&ft_routine_die_thinking, &philo[i]);
	else if (philo->time->way_to_die == SLEEPING)
		res = pthread_create(&time->philo_tid[i], NULL,
				(void *)&ft_routine_die_sleeping, &philo[i]);
	else
		res = pthread_create(&time->philo_tid[i], NULL,
				(void *)&ft_routine_principale, &philo[i]);
	return (res);
}

int	ft_find_philo(t_time *time, t_philo *philo, int i)
{
	int	res;

	res = 0;
	if (philo->time->way_to_die == ONE_PHILO)
		res = pthread_create(&time->philo_tid[i], NULL,
				(void *)&ft_routine_alone, &philo[i]);
	else if (philo->time->way_to_die == EATING)
		res = pthread_create(&time->philo_tid[i], NULL,
				(void *)&ft_routine_die_eating, &philo[i]);
	else if (philo->time->way_to_die == EAT_THEN_DIE)
		res = pthread_create(&time->philo_tid[i], NULL,
				(void *)&ft_routine_eat_then_die, &philo[i]);
	else if (philo->time->way_to_die == EAT_DIE_EVEN)
		res = pthread_create(&time->philo_tid[i], NULL,
				(void *)&ft_routine_die_thinking, &philo[i]);
	else
		res = ft_norme_philo(time, philo, res, i);
	if (res != 0)
		return (printf("error thread creation\n"), 1);
	return (0);
}
