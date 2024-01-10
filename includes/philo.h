/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfortin <kfortin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 11:05:13 by kfortin           #+#    #+#             */
/*   Updated: 2024/01/10 18:24:25 by kfortin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include "libft/libft.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

typedef struct s_fork
{
    int id;
    pthread_mutex_t *fork_mutex;
} t_fork;

typedef struct s_philo 
{
    pthread_t id;
    int *ptr;
    t_fork *fork;
}   t_philo;

typedef struct s_time
{
    int nbr_philo;
    int die;
    int eat;
    int sleep;
    int think;
    int nbr_cycle;
    int total;
    int max;
    int nbr_diner_left;
    t_philo *philo;
} t_time;



void ft_parsing(int argc, char **argv, t_time *time);
int ft_check_num(int argc, char **argv);

void ft_is_philo_die(t_time *time);
int ft_die_eating(t_time *time);
int ft_die_sleeping(t_time *time);
int ft_finish_eat_then_die(t_time *time);
int ft_die_thinking(t_time *time);
int ft_time_eat_die_even(t_time *time);
int ft_time_eat_die_odd(t_time *time);
int ft_nb_even(int nb);

void ft_init_struct(t_time *time);
void ft_init_thread(t_time *time);
void    *ft_routine_principale(void *arg);
#endif