/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmatjuhi <kmatjuhi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 11:42:07 by kmatjuhi          #+#    #+#             */
/*   Updated: 2024/04/08 13:49:26 by kmatjuhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_struct	intialize_t_struct(int argc, char **argv, int philo_nr)
{
	t_struct	p;
	int			i;

	p.philos = malloc(philo_nr * sizeof(t_philo));
	if (!p.philos)
		return (p);
	i = -1;
	while (++i <= philo_nr)
	{
		p.philos[i].x = i + 1;
		p.philos[i].die = atol(argv[2]);
		p.philos[i].eat = atol(argv[3]);
		p.philos[i].sleep = atol(argv[4]);
		p.philos[i].d_flag = 0;
		pthread_mutex_init(&p.philos[i].r_fork, NULL);
		if (argc == 6)
			p.philos[i].times_eat = atol(argv[5]);
	}
	if (p.philos[1].die < 0 || p.philos[1].eat < 0 || p.philos[1].sleep < 0)
	{
		free(p.philos);
		p.philos = NULL;
	}
	return (p);
}

int	main(int argc, char **argv)
{
	t_struct	p;

	if (argc != 5 && argc != 6)
		return (1);
	p.nr_philos = atol(argv[1]);
	if (p.nr_philos < 0)
		return (1);
	p = intialize_t_struct(argc, argv, p.nr_philos);
	if (!p.philos)
		return (1);
	if (tread(p) == 1)
	{
		free(p.philos);
		return (1);
	}
	free(p.philos);
	return (0);
}
