/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmatjuhi <kmatjuhi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 11:42:07 by kmatjuhi          #+#    #+#             */
/*   Updated: 2024/04/15 10:13:32 by kmatjuhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int argc, char **argv)
{
	t_struct	*p;

	if (argc != 5 && argc != 6)
		return (1);
	p = malloc(sizeof(t_struct));
	p->nr_philos = atol(argv[1]);
	if (p->nr_philos < 0)
		return (1);
	p->philos = malloc(p->nr_philos * sizeof(t_philo));
	if (init_mutex(p) == 1)
		return (1);
	init_struct(argc, argv, p);
	if (!p->philos)
		return (1);
	if (tread(p) == 1)
	{
		free(p->philos);
		return (1);
	}
	free(p->philos);
	free(p);
	return (0);
}
