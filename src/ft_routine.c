/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_routine.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfortin <kfortin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 13:12:11 by kfortin           #+#    #+#             */
/*   Updated: 2024/01/19 21:50:05 by kfortin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int     ft_check_status(t_philo *philo)
{
    int i;

    i = 0;
    while (i < philo->time->nbr_philo)
    {
        if (philo->time->status[i] == 1)
            return (1);
        i++;
    }
    return (0);
}

void    go_print(t_philo *philo, int i)
{
    if (ft_check_status(philo) == 0)
    {
        pthread_mutex_lock(&philo->time->print_mutex);
        if (i == FORK)
            printf("%zu %d has taken a fork\n", philo->time->tmp_last_diner, philo->id);
        if (i == EAT)
            printf("%zu %d is eating\n", philo->time->tmp_last_diner, philo->id);
        if (i == SLEEP)
            printf("%zu %d is sleeping\n", ft_get_time(philo), philo->id);
        if (i == THINK)
            printf("%zu %d is thinking\n", ft_get_time(philo), philo->id);
        if (i == DIE)
        {
            printf("%zu %d died\n", ft_get_time(philo), philo->id);
            if (philo->time->nbr_philo != 1)
            {
                pthread_mutex_lock(&philo->fork.fork_mutex_right);
                pthread_mutex_lock(philo->fork.fork_mutex_left);
            }
            philo->time->status[philo->id - 1] = 1;
            if (philo->time->nbr_philo != 1)
            {
                pthread_mutex_unlock(&philo->fork.fork_mutex_right);
                pthread_mutex_unlock(philo->fork.fork_mutex_left);
            }
        }
        pthread_mutex_unlock(&philo->time->print_mutex);
    }
}

void*   ft_routine_die_eating(t_philo *philo)
{
    pthread_mutex_lock(&philo->fork.fork_mutex_right);
    pthread_mutex_lock(philo->fork.fork_mutex_left);
        
    go_print(philo, FORK);
    go_print(philo, FORK);
    go_print(philo, EAT);
            
    pthread_mutex_lock(&philo->time->print_mutex);
    philo->time->tmp_last_diner = ft_get_time(philo);
    pthread_mutex_unlock(&philo->time->print_mutex);

    ft_usleep(philo->time->die, philo); 
        // printf("%zu check\n", ft_get_time(philo));
    pthread_mutex_unlock(&philo->fork.fork_mutex_right);
    pthread_mutex_unlock(philo->fork.fork_mutex_left);

    go_print(philo, DIE);
    pthread_exit(&philo->fork.fork_mutex_right);
}

void*   ft_routine_alone(t_philo *philo)
{
    pthread_mutex_lock(&philo->fork.fork_mutex_right);
    go_print(philo, FORK);
    ft_usleep(philo->time->die, philo);
    go_print(philo, DIE);
    pthread_exit(&philo->fork.fork_mutex_right);
}

void*   ft_routine_principale(t_philo *philo)
{   
    if (philo->id % 2 == 0)
        ft_usleep(100, philo);
    while (1)
    {
        ft_philo_eat(philo);
        ft_philo_sleep(philo);
        ft_philo_think(philo);
        ft_philo_die(philo);
    }
    pthread_exit(&philo->fork.fork_mutex_right);
    pthread_exit(philo->fork.fork_mutex_left);
}