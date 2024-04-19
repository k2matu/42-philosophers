/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmatjuhi <kmatjuhi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 11:42:07 by kmatjuhi          #+#    #+#             */
/*   Updated: 2024/04/19 15:28:57 by kmatjuhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	error_check(int argc, char **argv, t_struct *p)
{
	int	time;

	if (argc != 5 && argc != 6)
		return (0);
	p->dead_flag = -1;
	p->nr_philos = atol(argv[1]);
	if (p->nr_philos < 1)
		return (0);
	if (p->nr_philos == 1)
	{
		time = atol(argv[2]);
		if (time < 0)
			return (0);
		printf("%ld 1 has taken a fork\n", time_in_ms());
		usleep(time * 1000);
		printf("%ld 1 died\n", time_in_ms());
		return (2);
	}
	return (1);
}

int	main(int argc, char **argv)
{
	t_struct	p;
	int			i;

	i = error_check(argc, argv, &p);
	if (i == 0)
		return (1);
	if (i == 2)
		return (0);
	p.philos = malloc(p.nr_philos * sizeof(t_philo));
	if (!p.philos)
		return (1);
	if (!init(argc, argv, &p))
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
