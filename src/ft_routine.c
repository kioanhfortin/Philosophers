/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_routine.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfortin <kfortin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 13:12:11 by kfortin           #+#    #+#             */
/*   Updated: 2024/01/20 15:30:43 by kfortin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int     ft_check_status(t_philo *philo)
{
    int i;

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

void    go_print(t_philo *philo, int i)
{
    pthread_mutex_lock(&philo->time->stop_mutex);
    if (ft_check_status(philo) == 0)
    {
        pthread_mutex_lock(&philo->time->print_mutex);
        if (i == FORK)
            printf("%zu %d has taken a fork\n", ft_get_time(philo), philo->id);
        if (i == EAT)
            printf("%zu %d is eating\n", ft_get_time(philo), philo->id);
        if (i == SLEEP)
            printf("%zu %d is sleeping\n", ft_get_time(philo), philo->id);
        if (i == THINK)
            printf("%zu %d is thinking\n", ft_get_time(philo), philo->id);
        if (i == DIE)
        {
            printf("%zu %d died\n", ft_get_time(philo), philo->id);
            pthread_mutex_lock(&philo->time->status_mutex);
            philo->time->status[philo->id - 1] = 1;
            pthread_mutex_unlock(&philo->time->status_mutex);
        }
        pthread_mutex_unlock(&philo->time->print_mutex);
    }
    pthread_mutex_unlock(&philo->time->stop_mutex);
}

void*   ft_routine_eat_then_die(t_philo *philo)
{
    pthread_exit(&philo->fork.fork_mutex_right);
}

void*   ft_routine_die_sleeping(t_philo *philo)
{
    if (philo->id % 2 == 0)
        usleep(100);
    ft_philo_eat(philo);
    ft_usleep(philo->time->eat, philo);
    
    pthread_mutex_unlock(&philo->fork.fork_mutex_right);
    pthread_mutex_unlock(philo->fork.fork_mutex_left);

    go_print(philo, THINK);
    go_print(philo, SLEEP);
    ft_usleep(philo->time->sleep, philo);

    go_print(philo, DIE);
    pthread_exit(&philo->fork.fork_mutex_right);
}

void*   ft_routine_die_eating(t_philo *philo)
{
    if (philo->id % 2 == 0)
        usleep(100);
    ft_philo_eat(philo);
    ft_usleep(philo->time->die, philo); 
  
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
    while (1)
    {
        ft_philo_eat(philo);
        ft_usleep(philo->time->eat, philo);
        
        pthread_mutex_unlock(&philo->fork.fork_mutex_right);
        pthread_mutex_unlock(philo->fork.fork_mutex_left);
        
        go_print(philo, THINK);
        go_print(philo, SLEEP);
        ft_usleep(philo->time->sleep, philo);
    }
}