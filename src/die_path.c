/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   die_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfortin <kfortin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 14:01:28 by kfortin           #+#    #+#             */
/*   Updated: 2024/01/20 14:56:33 by kfortin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int ft_die_eating(t_time *time)
{
    if (time->eat > time->die)
    {
        time->total_time_before_death = time->die;
        return (1);
    }
    return (0);
}

int ft_die_sleeping(t_time *time)
{
    if (time->eat + time->sleep == time->die)
        return (1);
    return(0);
}

int ft_finish_eat_then_die(t_time *time)
{
    if (time->die + time->eat == time->die)
        return (1);
    return (0);
}

int ft_die_thinking(t_time *time)
{
    (void)time;
    //if ?
    return (0);
}

int ft_time_eat_die_even(t_time *time)
{
    if (time->eat > time->sleep && ft_nb_even(time->nbr_philo) == 1 && time->die <= time->eat * 2)
        return(1);
    return (0);
}

int ft_time_eat_die_odd(t_time *time)
{
    if (time->eat > time->sleep && ft_nb_even(time->nbr_philo) == 0 && time->die <= time->eat * 3)
        return (1);
    return (0);
}

void ft_is_philo_die(t_time *time)
{
    int       (*built_tab[7])(t_time*);
    int count;
    
    count = 1;
    built_tab[1] = ft_die_eating;
    built_tab[2] = ft_die_sleeping;
    built_tab[3] = ft_finish_eat_then_die;
    built_tab[4] = ft_die_thinking;
    built_tab[5] = ft_time_eat_die_even;
    built_tab[6] = ft_time_eat_die_odd;

    while (count < 7)
    {
        // printf("way to die :%d\n", count);
        if ((built_tab[count])(time) == 1)
            break;
        count++;
    }
    if (time->nbr_philo == 1)
    {
            // printf("die while eating\n");
            time->total_time_before_death = time->eat + time->sleep;
            // printf("total_time_before_death %d\n", time->total_time_before_death);
            time->way_to_die = ONE_PHILO;
    }
    else
    {
        time->way_to_die = count;
    }
}
