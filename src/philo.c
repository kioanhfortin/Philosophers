/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfortin <kfortin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 11:10:53 by kfortin           #+#    #+#             */
/*   Updated: 2024/02/13 17:03:41 by kfortin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_check_num(int argc, char **argv)
{
	int		i;
	size_t	j;

	i = 1;
	while (i < argc)
	{
		j = 0;
		if (ft_atoi(argv[i]) < 0 || ft_atoi(argv[i]) > 2147483647)
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

void	ft_parsing(int argc, char **argv, t_time *time)
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

int	main(int argc, char **argv)
{
	t_philo	*philo;
	t_time	*time;

	philo = NULL;
	time = ft_calloc(sizeof(struct s_time), 1);
	if (!time)
		return (-1);
	if (argc == 5 || argc == 6)
	{
		if (ft_check_num(argc, argv) == 1)
		{
			ft_parsing(argc, argv, time);
			ft_init_philo(time, philo);
		}
		else
			printf("error parsing\n");
	}
	else
		printf("error number of arguments\n");
	if (time)
		free(time);
	return (0);
}
