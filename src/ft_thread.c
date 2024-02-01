/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_thread.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfortin <kfortin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 14:38:32 by kfortin           #+#    #+#             */
/*   Updated: 2024/02/01 05:26:30 by kfortin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    ft_init_mutex_struct(t_time *time)
{
    int i;

    i = 0;
    pthread_mutex_init(&time->print_mutex, NULL);
    pthread_mutex_init(&time->last_diner_mutex, NULL);
    pthread_mutex_init(&time->status_mutex, NULL);
    pthread_mutex_init(&time->status_fork_mutex, NULL);
    pthread_mutex_init(&time->stop_mutex, NULL);
    pthread_mutex_init(&time->cycle_mutex, NULL);
    while (i < time->nbr_philo)
    {
        pthread_mutex_init(&philo[i].fork.fork_mutex_right, NULL);
        i++;
    }
    i = 0;
    while (i < time->nbr_philo)
    {
        if (i > 0)
            philo[i].fork.fork_mutex_left = &philo[i - 1].fork.fork_mutex_right;
        else if (philo->time->nbr_philo != 1)
            philo[i].fork.fork_mutex_left = &philo[time->nbr_philo - 1].fork.fork_mutex_right;
        i++;
    }
}

void ft_init_thread(t_time *time, t_philo *philo)
{   
    int i;
    
    i = 0;
    gettimeofday(&philo->time->start, NULL);
    ft_init_mutex_struct(time, philo);
    while(i < time->nbr_philo)
    {
        // if (philo->id % 2 == 0)
        //     usleep(philo->time->eat / 2);
        // printf("way to die :%d\n", philo->time->way_to_die);
        if (philo->time->way_to_die == ONE_PHILO)
            pthread_create(&time->philo_tid[i], NULL, (void*)&ft_routine_alone, &philo[i]);
        else if (philo->time->way_to_die == EATING)
            pthread_create(&time->philo_tid[i], NULL, (void*)&ft_routine_die_eating, &philo[i]);
        else if (philo->time->way_to_die == SLEEPING)
            pthread_create(&time->philo_tid[i], NULL, (void*)&ft_routine_die_sleeping, &philo[i]);
        else if (philo->time->way_to_die == EAT_THEN_DIE)
            pthread_create(&time->philo_tid[i], NULL, (void*)&ft_routine_eat_then_die, &philo[i]);
        else if (philo->time->way_to_die == THINKING)
            pthread_create(&time->philo_tid[i], NULL, (void*)&ft_routine_die_thinking, &philo[i]);
        else
            pthread_create(&time->philo_tid[i], NULL, (void*)&ft_routine_principale, &philo[i]);
        i++;
    }
    // ft_checker(philo);
    //wait for philo to finish
    ft_join_and_destroy(time, philo);
}

void    ft_join_and_destroy(t_time *time, t_philo *philo)
{
    int i;

    i = 0;
    while (i < time->nbr_philo)
    {
        pthread_join(time->philo_tid[i], (void**)&philo->ptr);
        i++;
    }
    i = 0;
    while (i < time->nbr_philo)
    {
        pthread_mutex_destroy(&philo[i].fork.fork_mutex_right);
        i++;
    }
}
