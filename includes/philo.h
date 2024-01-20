/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfortin <kfortin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 11:05:13 by kfortin           #+#    #+#             */
/*   Updated: 2024/01/20 14:56:07 by kfortin          ###   ########.fr       */
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

typedef enum e_die
{
	ONE_PHILO,
	EATING,
	SLEEPING,
	EAT_THEN_DIE,
	THINKING,
	EAT_DIE_EVEN,
    EAT_DIE_ODD,
    DONT_DIE,
} t_die;

typedef enum e_print
{
    FORK,
	EAT,
	SLEEP,
	THINK,
    DIE,
} t_print;

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
    pthread_mutex_t last_diner_mutex;
    int stop;
    pthread_mutex_t stop_mutex;
    int total;
    int max;
    int total_time_before_death;
    int nbr_diner_left;
    int way_to_die;
    int *status;
    pthread_mutex_t status_mutex;
    pthread_t *philo_tid;
    pthread_mutex_t print_mutex;
    struct s_philo *philo;
    struct timeval start;
} t_time;

typedef struct s_philo 
{
    int id;
    // int status;
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

void    ft_usleep(long tim, t_philo *philo);
int ft_init_philo(t_time *time, t_philo *philo);
void ft_init_thread(t_time *time, t_philo *philo);
time_t    ft_get_time(t_philo *philo);

void*   ft_routine_alone(t_philo *philo);
void*   ft_routine_die_eating(t_philo *philo);
void*   ft_routine_die_sleeping(t_philo *philo);
void*   ft_routine_eat_then_die(t_philo *philo);
void*   ft_routine_principale(t_philo *philo);

void    ft_philo_eat(t_philo *philo);
void    ft_philo_sleep(t_philo *philo);
void    ft_philo_think(t_philo *philo);
void    ft_philo_die(t_philo *philo);

void    go_print(t_philo *philo, int i);
int     ft_check_status(t_philo *philo);

int ft_checker(t_philo *philo);

#endif