/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_thread.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfortin <kfortin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 14:38:32 by kfortin           #+#    #+#             */
/*   Updated: 2024/01/10 18:26:01 by kfortin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    *ft_routine_principale(void *arg)
{
    (void)arg;
    printf("run routine\n");
    return (NULL);
}

void ft_init_struct(t_time *time)
{
    int i;
    i = 0;
    
    //init philo & init fork
    time->philo = ft_calloc(sizeof(t_philo), time->nbr_philo);
    while (i < time->nbr_philo)
    {
        time->philo[i].fork = ft_calloc(1, sizeof(t_fork));
        i++;
    }
}

void ft_init_thread(t_time *time)
{
    // (void)time;
    int i;
    i = 0;
    //init mutex
    while (i < time->nbr_philo)
    {
        pthread_mutex_init(time->philo[i].fork->fork_mutex, NULL);   
        i++;
    }
    //init pthread
    i = 0;
    while(i < time->nbr_philo)
    {
        // time->philo[i].id = i;
        pthread_create(&time->philo[i].id, NULL, ft_routine_principale, &time->philo[i].id);
        i++;
    }
    //wait for philo to finish
    i = 0;
    while (i < time->nbr_philo)
    {
        pthread_joint(&time->philo[i].id, (void**)&time->philo->ptr);
        i++;
    }
    //detruire les mutex
    // i = 0;
    // while (i < time->nbr_philo)
    // {
    //     pthread_mutex_destroy(&time->philo[i].fork->fork_mutex);
    //     i++;
    // }
}
