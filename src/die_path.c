/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   die_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfortin <kfortin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 14:01:28 by kfortin           #+#    #+#             */
/*   Updated: 2023/09/26 15:31:27 by kfortin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int ft_die_eating(t_time *time)
{
    time->total = (time->nbr_cycle * time->eat) + (time->nbr_philo * time->sleep);
    time->max = (time->eat + time->sleep) * time->nbr_cycle;
    if (time->total >= time->max)
        return (1);
    return (0);
}

int ft_die_sleeping(t_time *time)
{
    time->max = (time->eat + time->sleep) * time->nbr_cycle;
    time->nbr_diner_left = time->max / (time->eat + time->sleep) - time->nbr_cycle;
    if (time->nbr_diner_left <= 0)
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
    if (time->nbr_philo == 1)
    {
        printf("die while eating\n");
        //take a fork and die
    }
    else if (ft_die_eating(time) == 1)
    {
        printf("die while eating\n");
          //go to path
    }
    else if (ft_die_sleeping(time) == 1)
    {
        printf("die while sleeping\n");
          //go to path
    }
    else if (ft_finish_eat_then_die(time) == 1)
    {
        printf("dying when was about to finish eating\n");
          //go to path
    }
    else if (ft_die_thinking(time) == 1)
    {
        printf("die while thinking\n");
          //go to path
    }
    else if (ft_time_eat_die_even(time) == 1)
    {
        printf("not enougt time to eat - even\n");
          //go to path
    }
    else if (ft_time_eat_die_odd(time) == 1)
    {
        printf("not enougt time to eat - odd\n");
          //go to path
    }
    else
    {
        //ft_count_cycle(time);
    }
}