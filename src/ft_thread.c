/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_thread.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfortin <kfortin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 14:38:32 by kfortin           #+#    #+#             */
/*   Updated: 2024/01/21 13:04:26 by kfortin          ###   ########.fr       */
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
    pthread_mutex_lock(philo->fork.fork_mutex_left);
    
    pthread_mutex_lock(&philo->time->status_fork_mutex);
    if (philo->id != 0)
        philo->time->status_fork[philo->id - 1] = 1;
    else
        philo->time->status_fork[philo->time->nbr_philo] = 1;
    pthread_mutex_unlock(&philo->time->status_fork_mutex);

    go_print(philo, FORK);
    go_print(philo, FORK);
    go_print(philo, EAT);
    
    pthread_mutex_lock(&philo->time->last_diner_mutex);
    philo->time->tmp_last_diner = ft_get_time(philo);
    pthread_mutex_unlock(&philo->time->last_diner_mutex);
}

// void    ft_philo_sleep(t_philo *philo)
// {
//     ft_usleep(philo->time->sleep, philo);
//     printf("%zu %d is sleeping\n", ft_get_time(philo), philo->id);
// }

int     ft_check_status_fork(t_philo *philo)
{
    pthread_mutex_lock(&philo->time->status_fork_mutex);
    if (philo->time->status_fork[philo->id] == 1 || (philo->id != 1 && philo->time->status_fork[philo->id - 1] == 1) || (philo->id == 1 && philo->time->status_fork[philo->time->nbr_cycle] == 1))
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

void    ft_philo_think(t_philo *philo)
{
    if (ft_check_status_fork(philo) == 0)
    {
        go_print(philo, THINK);
        ft_usleep(philo->time->eat, philo);
    }
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
    pthread_mutex_init(&time->print_mutex, NULL);
    pthread_mutex_init(&time->last_diner_mutex, NULL);
    pthread_mutex_init(&time->status_mutex, NULL);
    pthread_mutex_init(&time->status_fork_mutex, NULL);
    pthread_mutex_init(&time->stop_mutex, NULL);
    pthread_mutex_init(&time->cycle_mutex, NULL);
    //init mutex
    while (i < time->nbr_philo)
    {
        pthread_mutex_init(&philo[i].fork.fork_mutex_right, NULL);
        i++;
    }
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
        // if (philo->id % 2 == 0)
        //     usleep(philo->time->eat / 2);
        // printf("way to die :%d\n", philo->time->way_to_die);
        if (philo->time->way_to_die == ONE_PHILO)
        {
            pthread_create(&time->philo_tid[i], NULL, (void*)&ft_routine_alone, &philo[i]);
        }
        else if (philo->time->way_to_die == EATING)
        {
            pthread_create(&time->philo_tid[i], NULL, (void*)&ft_routine_die_eating, &philo[i]);
        }
        else if (philo->time->way_to_die == SLEEPING)
        {
            pthread_create(&time->philo_tid[i], NULL, (void*)&ft_routine_die_sleeping, &philo[i]);
        }
        else if (philo->time->way_to_die == EAT_THEN_DIE)
        {
            pthread_create(&time->philo_tid[i], NULL, (void*)&ft_routine_eat_then_die, &philo[i]);
        }
        else if (philo->time->way_to_die == THINKING)
        {
            pthread_create(&time->philo_tid[i], NULL, (void*)&ft_routine_die_thinking, &philo[i]);
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
