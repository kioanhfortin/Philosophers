/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfortin <kfortin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 11:05:13 by kfortin           #+#    #+#             */
/*   Updated: 2024/01/12 18:17:43 by kfortin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include "libft/libft.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <sys/time.h>

typedef struct s_fork
{
    // int id;
    pthread_mutex_t fork_mutex_right;
    pthread_mutex_t *fork_mutex_left;
} t_fork;

typedef struct s_time
{
    int nbr_philo;
    int die;
    int eat;
    int sleep;
    int think;
    int nbr_cycle;
    time_t tmp_last_diner;
    int stop;
    int total;
    int max;
    int nbr_diner_left;
    pthread_t *philo_tid;
    struct s_philo *philo;
    struct timeval start;
} t_time;

typedef struct s_philo 
{
    int id;
    int status;
    int *ptr;
    t_fork fork;
    t_time *time;
}   t_philo;

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

int ft_init_philo(t_time *time, t_philo *philo);
void ft_init_thread(t_time *time, t_philo *philo);
time_t    ft_get_time(t_philo *philo);
void*   ft_routine_principale(t_philo *philo);

void    ft_philo_eat(t_philo *philo);
void    ft_philo_sleep(t_philo *philo);
void    ft_philo_think(t_philo *philo);
void    ft_philo_die(t_philo *philo);

int ft_checker(t_philo *philo);

#endif