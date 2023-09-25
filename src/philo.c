/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfortin <kfortin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 11:10:53 by kfortin           #+#    #+#             */
/*   Updated: 2023/09/25 11:46:41 by kfortin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void ft_parsing(char **argv, t_time *time)
{
    time->nbr_philo = ft_atoi(argv[1]);
    time->die = ft_atoi(argv[2]);
    time->eat = ft_atoi(argv[3]);
    time->sleep = ft_atoi(argv[4]);
    time->nbr_cycle = ft_atoi(argv[5]);
}

int main(int argc, char **argv)
{
    t_time *time;

    time = ft_calloc(sizeof(struct s_time), 1);
    if (!time)
        return (-1);
    if (argc == 6)
    {
        ft_parsing(argv, time);
    }
    printf("nbr philo : %d\ntime die : %d\ntime eat : %d\ntime spleep %d\nnbr cycle : %d\n", time->nbr_philo, time->die, time->eat, time->sleep, time->nbr_cycle);
    return(0);
    // parsing should receive number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
}