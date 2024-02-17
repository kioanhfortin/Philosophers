/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfortin <kfortin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 11:10:53 by kfortin           #+#    #+#             */
/*   Updated: 2024/02/17 16:49:51 by kfortin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (s1[i] - s2[i]);
}

int	ft_check_num(int argc, char **argv)
{
	int		i;
	size_t	j;

	i = 1;
	while (i < argc)
	{
		j = 0;
		if (ft_strlen(argv[i]) > 10 || (ft_strlen(argv[i]) == 10
				&& ft_strcmp(argv[i], "2147483647") > 0))
			return (0);
		while (j < ft_strlen(argv[i]))
		{
			if (ft_isdigit(argv[i][j]) == 0)
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int	ft_parsing(int argc, char **argv, t_time *time)
{
	time->nbr_philo = ft_atoi(argv[1]);
	time->die = ft_atoi(argv[2]);
	time->eat = ft_atoi(argv[3]);
	time->sleep = ft_atoi(argv[4]);
	if (time->nbr_philo == 0 || time->die < 60 || time->eat < 60
		|| time->sleep < 60)
		return (1);
	if (argc == 6)
	{
		if (ft_atoi(argv[5]) == 0)
			return (1);
		time->nbr_cycle = ft_atoi(argv[5]);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_philo	*philo;
	t_time	*time;

	philo = NULL;
	time = ft_calloc(sizeof(struct s_time), 1);
	if (!time)
		return (1);
	if (argc == 5 || argc == 6)
	{
		if (ft_check_num(argc, argv) == 1)
		{
			if (ft_parsing(argc, argv, time) == 1)
				return (ft_free_all(time), 0);
			if (ft_init_philo(time, philo) == 1)
				return (ft_free_all(time), printf("error memory usage\n"), 1);
		}
		else
			return (ft_free_all(time), printf("error parsing\n"), 1);
	}
	else
		return (ft_free_all(time), printf("error number of arguments\n"), 1);
	return (ft_free_all(time), 0);
}
