/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_routine.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfortin <kfortin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 13:12:11 by kfortin           #+#    #+#             */
/*   Updated: 2024/01/13 14:50:39 by kfortin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void*   ft_routine_die_eating(t_philo *philo)
{
    printf("%d\n", philo->time->way_to_die);
    if (philo->time->way_to_die == ONE_PHILO)
    {
        while (philo->time->total_time_before_death > ft_get_time(philo))
        {
            ft_philo_eat(philo);
            ft_philo_sleep(philo);
            ft_philo_think(philo);
            if (philo->time->total_time_before_death <= ft_get_time(philo))
                break;
        }
        ft_philo_die(philo);
    }
    // if (philo->time->way_to_die == DONT_DIE)
    // {
    //     ft_routine_principale(philo);
    // }
    pthread_exit(&philo->fork.fork_mutex_right);
    // pthread_exit(philo->fork.fork_mutex_left);
}