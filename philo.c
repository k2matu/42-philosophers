/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmatjuhi <kmatjuhi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 11:42:07 by kmatjuhi          #+#    #+#             */
/*   Updated: 2024/07/04 11:28:16 by kmatjuhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	error_check(int argc, char **argv, t_struct *p)
{
	p->nr_philos = atol(argv[1]);
	if (p->nr_philos < 1)
		return (error_msg("Min 1 philosopher required"));
	p->die = atol(argv[2]);
	p->eat = atol(argv[3]);
	p->sleep = atol(argv[4]);
	if (argc == 6)
		p->times_eat = atol(argv[5]);
	if (p->die < 0 || p->eat < 0 \
	|| p->sleep < 0 || (argc == 6 && p->times_eat < 0))
		return (error_msg("Min 60 ms"));
	if (p->nr_philos == 1)
	{
		printf("%ld 1 has taken a fork\n", time_in_ms());
		usleep(p->die * 1000);
		printf("%ld 1 died\n", time_in_ms());
		return (2);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_struct	p;
	int			i;

	if (argc != 5 && argc != 6)
		return (error_msg("Your program should take 4 or 5 arguments"));
	p.dead_flag = -1;
	i = error_check(argc, argv, &p);
	if (i == 1)
		return (1);
	if (i == 2)
		return (0);
	p.philos = malloc(p.nr_philos * sizeof(t_philo));
	if (!p.philos)
		return (error_msg("Malloc failed"));
	if (!init(argc, &p))
		return (1);
	if (!tread(&p))
	{
		free(p.philos);
		return (1);
	}
	free(p.philos);
	pthread_mutex_destroy(p.forks);
	free(p.forks);
	return (0);
}
