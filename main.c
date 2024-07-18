/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmatjuhi <kmatjuhi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 11:42:07 by kmatjuhi          #+#    #+#             */
/*   Updated: 2024/07/18 10:58:37 by kmatjuhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	error_check(int argc, char **argv, t_struct *p)
{
	p->nr_philos = p_atol(argv[1]);
	if (p->nr_philos < 1)
		return (error_msg("Min 1 philosopher required", 1));
	p->die = p_atol(argv[2]);
	p->eat = p_atol(argv[3]);
	p->sleep = p_atol(argv[4]);
	if (argc == 6)
		p->times_eat = p_atol(argv[5]);
	if (p->die < 0 || p->eat < 0 \
	|| p->sleep < 0 || (argc == 6 && p->times_eat < 0))
		return (error_msg("Invalid input", 1));
	return (0);
}

int	main(int argc, char **argv)
{
	t_struct	p;
	int			i;

	if (argc != 5 && argc != 6)
		return (error_msg("Your program should take 4 or 5 arguments", 1));
	p.dead_flag = -1;
	i = error_check(argc, argv, &p);
	if (i == 1)
		return (1);
	p.philos = malloc(p.nr_philos * sizeof(t_philo));
	if (!p.philos)
		return (error_msg("Malloc failed", 1));
	if (!init(argc, &p))
		return (1);
	if (!tread(&p))
	{
		cleanup_resources(&p, p.nr_philos);
		return (1);
	}
	cleanup_resources(&p, p.nr_philos);
	return (0);
}
