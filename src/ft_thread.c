/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_thread.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfortin <kfortin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 14:38:32 by kfortin           #+#    #+#             */
/*   Updated: 2024/01/19 21:27:21 by kfortin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

time_t    ft_get_time(t_philo *philo)
{
    struct timeval end;
    
    gettimeofday(&end, NULL);
    return ((end.tv_sec - philo->time->start.tv_sec) * 1000 + (end.tv_usec - philo->time->start.tv_usec) / 1000);
}

void    ft_philo_eat(t_philo *philo)
{
    pthread_mutex_lock(&philo->fork.fork_mutex_right);
    pthread_mutex_lock(&philo->time->print_mutex);
    printf("%zu %d has taken a fork\n", philo->time->tmp_last_diner, philo->id);
    pthread_mutex_lock(philo->fork.fork_mutex_left);
    printf("%zu %d has taken a fork\n", philo->time->tmp_last_diner, philo->id);    
    printf("%zu %d is eating\n", philo->time->tmp_last_diner, philo->id);
    philo->time->tmp_last_diner = ft_get_time(philo);
    ft_usleep(philo->time->eat, philo);
    pthread_mutex_unlock(&philo->time->print_mutex);
    pthread_mutex_unlock(&philo->fork.fork_mutex_right);
    pthread_mutex_unlock(philo->fork.fork_mutex_left);
}

void    ft_philo_sleep(t_philo *philo)
{
    ft_usleep(philo->time->sleep, philo);
    printf("%zu %d is sleeping\n", ft_get_time(philo), philo->id);
}

void    ft_philo_think(t_philo *philo)
{
    printf("%zu %d is thinking\n", ft_get_time(philo), philo->id);
}

void    ft_philo_die(t_philo *philo)
{
    // time_t time_elapsed;
    
    // time_elapsed = ft_get_time(philo) - philo->time->tmp_last_diner;
    // if (time_elapsed > philo->time->die)
    // {
    pthread_mutex_lock(&philo->time->print_mutex);
    printf("%zu %d died\n", ft_get_time(philo), philo->id);
    pthread_mutex_unlock(&philo->time->print_mutex);
        // philo->status = 1;
    // }
}

// int ft_checker(t_philo *philo)
// {
//     int i;

//     i = 0;
//     while(1)
//     {
//         while (i < philo->time->nbr_philo)
//         {
//             if (philo->time->status[i] == 1)
//                 philo->time->stop = 1;
//             i++;
//         }
//     }
// }

void ft_init_thread(t_time *time, t_philo *philo)
{   
    int i;
    
    i = 0;
    gettimeofday(&philo->time->start, NULL);
    //init mutex
    while (i < time->nbr_philo)
    {
        pthread_mutex_init(&philo[i].fork.fork_mutex_right, NULL);
        i++;
    }
    pthread_mutex_init(&time->print_mutex, NULL);
    //attribuer mutex a gauche
    i = 0;
    while (i < time->nbr_philo)
    {
        if (i > 0)
            philo[i].fork.fork_mutex_left = &philo[i - 1].fork.fork_mutex_right;
        else if (philo->time->nbr_philo != 1)
            philo[i].fork.fork_mutex_left = &philo[time->nbr_philo - 1].fork.fork_mutex_right;
        i++;
    }
    //init pthread
    i = 0;
    while(i < time->nbr_philo)
    {
        // printf("way to die :%d\n", philo->time->way_to_die);
        if (philo->time->way_to_die == ONE_PHILO)
        {
            pthread_create(&time->philo_tid[i], NULL, (void*)&ft_routine_alone, &philo[i]);
        }
        else if (philo->time->way_to_die == EATING)
        {
            pthread_create(&time->philo_tid[i], NULL, (void*)&ft_routine_die_eating, &philo[i]);
        }
        else
            pthread_create(&time->philo_tid[i], NULL, (void*)&ft_routine_principale, &philo[i]);
        i++;
    }
    // ft_checker(philo);
    //wait for philo to finish
    i = 0;
    while (i < time->nbr_philo)
    {
        pthread_join(time->philo_tid[i], (void**)&philo->ptr);
        i++;
    }
    //detruire les mutex
    i = 0;
    while (i < time->nbr_philo)
    {
        pthread_mutex_destroy(&philo[i].fork.fork_mutex_right);
        i++;
    }
}
