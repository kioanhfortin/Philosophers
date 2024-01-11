/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_thread.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfortin <kfortin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 14:38:32 by kfortin           #+#    #+#             */
/*   Updated: 2024/01/11 16:22:17 by kfortin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

unsigned long     ft_get_time()
{
    struct timeval start = {-1, -1};
    struct timeval end;
    unsigned long milsec;
    
    if (start.tv_sec == -1 && start.tv_usec == -1)
        gettimeofday(&start, NULL);
    gettimeofday(&end, NULL);
    milsec = ((end.tv_sec * 1000) + end.tv_usec) - ((start.tv_sec * 1000) + start.tv_usec);
    return (milsec);
}

void*   ft_routine_principale(void *arg)
{
    // unsigned long time;
    t_philo *philo;
    
    philo = arg;
    // philo->time->tim = ft_get_time();
    pthread_mutex_lock(&philo->fork.fork_mutex_right);
    printf("%zu has taken a fork\n", ft_get_time());
    usleep(50);
    printf("%zu has taken a fork2\n", ft_get_time());
    usleep(50);
    pthread_mutex_unlock(&philo->fork.fork_mutex_right);
    pthread_exit(&philo->fork.fork_mutex_right);
}

void ft_init_thread(t_time *time)
{
    // (void)time;
    // unsigned long tim;
    int i;
    i = 0;
    //init mutex
    time->tim = ft_get_time();
    while (i < time->nbr_philo)
    {
        pthread_mutex_init(&time->philo[i].fork.fork_mutex_right, NULL);
        i++;
    }
    //attribuer mutex a gauche
    i = 0;
    while (i < time->nbr_philo)
    {
        if (i > 0)
            time->philo[i].fork.fork_mutex_left = time->philo[i - 1].fork.fork_mutex_left;
        else
            time->philo[i].fork.fork_mutex_left = time->philo[time->nbr_philo - 1].fork.fork_mutex_left;
        i++;
    }
    //init pthread
    i = 0;
    while(i < time->nbr_philo)
    {
        // time->philo[i].id = i;
        pthread_create(&time->philo[i].id, NULL, ft_routine_principale, &time->philo[i]);
        i++;
    }
    //wait for philo to finish
    i = 0;
    while (i < time->nbr_philo)
    {
        pthread_join(time->philo[i].id, (void**)&time->philo->ptr);
        i++;
    }
    //detruire les mutex
    i = 0;
    while (i < time->nbr_philo)
    {
        pthread_mutex_destroy(&time->philo[i].fork.fork_mutex_right);
        i++;
    }
}
