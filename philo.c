/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmatjuhi <kmatjuhi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 11:42:07 by kmatjuhi          #+#    #+#             */
/*   Updated: 2024/04/16 10:49:42 by kmatjuhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int argc, char **argv)
{
	t_struct	*p;

	if (argc != 5 && argc != 6)
		return (1);
	p = (t_struct *)malloc(sizeof(t_struct));
	if (!p)
		return (1);
	p->nr_philos = atol(argv[1]);
	if (p->nr_philos < 0)
		return (1);
	p->philos = malloc(p->nr_philos * sizeof(t_philo));
	if (!p->philos)
	{
		free(p);
		return (1);
	}
	if (init_mutex(p) == 1)
	{
		free(p->philos);
		free(p);
		return (1);
	}
	init_struct(argc, argv, p);
	if (tread(p) == 1)
	{
		free(p->philos);
		return (1);
	}
	free(p->philos);
	pthread_mutex_destroy(p->forks);
	free(p->forks);
	free(p);
	return (0);
}
