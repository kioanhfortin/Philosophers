/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utilis.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfortin <kfortin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 15:25:24 by kfortin           #+#    #+#             */
/*   Updated: 2024/01/12 18:17:59 by kfortin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int ft_nb_even(int nb)
{
    if (nb % 2 == 0)
        return (1);
    return (0);
}

int ft_init_philo(t_time *time, t_philo *philo)
{
    int i;
    
    i = 0;
    philo = ft_calloc(sizeof(struct s_philo), time->nbr_philo);
    if (!philo)
        return (-1);
    time->philo_tid = ft_calloc(sizeof(pthread_t), time->nbr_philo);
    if (!time->philo_tid)
        return (-1);
    time->philo = philo;
    while (i < time->nbr_philo)
    {
        philo[i].time = time;
        philo[i].id = i + 1;
        i++;
    }
    ft_is_philo_die(time);
    time->stop = 0;
    ft_init_thread(time, philo);
    return(0);
}