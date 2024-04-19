/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmatjuhi <kmatjuhi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 11:42:07 by kmatjuhi          #+#    #+#             */
/*   Updated: 2024/04/18 12:07:37 by kmatjuhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int argc, char **argv)
{
	t_struct	p;

	if (argc != 5 && argc != 6)
		return (1);
	p.dead_flag = -1;
	p.nr_philos = atol(argv[1]);
	if (p.nr_philos < 1)
		return (1);
	if (p.nr_philos == 1)
	{
		printf("%ld 1 died\n", time_in_ms());
		return (0);
	}
	p.philos = malloc(p.nr_philos * sizeof(t_philo));
	if (!p.philos)
		return (1);
	if (init_mutex(&p) == 1)
	{
		free(p.philos);
		return (1);
	}
	init_struct(argc, argv, &p);
	if (tread(&p) == 1)
	{
		free(p.philos);
		return (1);
	}
	free(p.philos);
	pthread_mutex_destroy(p.forks);
	free(p.forks);
	return (0);
}
