/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfortin <kfortin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 11:10:53 by kfortin           #+#    #+#             */
/*   Updated: 2023/09/26 15:37:49 by kfortin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int ft_check_num(int argc, char **argv)
{
    int i;
    size_t j;

    i = 1;
    while (i < argc)
    {
        j = 0;
        if (ft_atoi(argv[i]) < 0 || ft_atoi(argv[i]) > 2147483647)
            return (0);
        while(j < ft_strlen(argv[i]))
        {
            if (ft_isdigit(argv[i][j]) == 0)
                return (0);
            j++;
        }
        i++;
    }
    return(1);
}

void ft_parsing(int argc, char **argv, t_time *time)
{
    if (ft_check_num(argc, argv) == 1)
    {
        time->nbr_philo = ft_atoi(argv[1]);
        time->die = ft_atoi(argv[2]);
        time->eat = ft_atoi(argv[3]);
        time->sleep = ft_atoi(argv[4]);
        if (argc == 6)
            time->nbr_cycle = ft_atoi(argv[5]);
    }
    else
        printf("error parsing\n");
}

int main(int argc, char **argv)
{
    t_time *time;

    time = ft_calloc(sizeof(struct s_time), 1);
    if (!time)
        return (-1);
    if (argc == 5 || argc == 6)
    {
        if (ft_check_num(argc, argv) == 1)
        {
            ft_parsing(argc, argv, time);
            ft_is_philo_die(time);
        }
        else
            printf("error parsing\n");
    }
    else
        printf("error number of arguments\n");
    printf("nbr philo : %d\ntime die : %d\ntime eat : %d\ntime spleep %d\nnbr cycle : %d\n", time->nbr_philo, time->die, time->eat, time->sleep, time->nbr_cycle);
    if(time)
        free(time);
    return(0);
    // 4 or 5 argument - number of cycle is optional
    // if 4 no limit
}