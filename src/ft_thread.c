/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_thread.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfortin <kfortin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 14:38:32 by kfortin           #+#    #+#             */
/*   Updated: 2024/01/12 20:01:19 by kfortin          ###   ########.fr       */
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
    philo->time->tmp_last_diner = ft_get_time(philo);
    // printf("temps dernier repas : %zu\n", philo->time->tmp_last_diner);
    ft_usleep(philo->time->eat, philo);
    printf("%zu philo %d has taken a fork\n", philo->time->tmp_last_diner, philo->id);
    pthread_mutex_unlock(&philo->fork.fork_mutex_right);
    pthread_mutex_unlock(philo->fork.fork_mutex_left);
}

void    ft_philo_sleep(t_philo *philo)
{
    ft_usleep(philo->time->sleep, philo);
    printf("%zu philo %d is sleeping\n", ft_get_time(philo), philo->id);
}

void    ft_philo_think(t_philo *philo)
{
    printf("%zu philo %d is thinking\n", ft_get_time(philo), philo->id);
}

void    ft_philo_die(t_philo *philo)
{
    time_t time_elapsed;
    
    time_elapsed = ft_get_time(philo) - philo->time->tmp_last_diner;
    if (time_elapsed > philo->time->die)
    {
        printf("%zu philo %d is dead\n", ft_get_time(philo), philo->id);
        philo->status = 1;
    }
}

void*   ft_routine_principale(t_philo *philo)
{   
    if (philo->id % 2 == 0)
        ft_usleep(100, philo);
    printf("stop flag : %d\n", philo->time->stop);
    while (philo->time->stop == 0)
    {
        if (philo->time->stop == 1)
            break;
        printf("main boucle %d\n", philo->status);
        ft_philo_eat(philo);
        ft_philo_sleep(philo);
        ft_philo_think(philo);
        ft_philo_die(philo);
        if (philo->time->stop == 1)
            break;
    }
    pthread_exit(&philo->fork.fork_mutex_right);
}

int ft_checker(t_philo *philo)
{
    int i;

    i = 0;
    while(1)
    {
        while (i < philo->time->nbr_philo)
        {
            if (philo[i].status == 1)
                philo->time->stop = 1;
            i++;
        }
    }
}

void ft_init_thread(t_time *time, t_philo *philo)
{   
    int i;
    
    i = 0;
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
        else
            philo[i].fork.fork_mutex_left = &philo[time->nbr_philo].fork.fork_mutex_right;
        i++;
    }
    //init pthread
    gettimeofday(&philo->time->start, NULL);
    i = 0;
    while(i < time->nbr_philo)
    {
        pthread_create(&time->philo_tid[i], NULL, (void*)&ft_routine_principale, &philo[i]);
        i++;
    }
    ft_checker(philo);
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
