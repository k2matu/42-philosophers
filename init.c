/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmatjuhi <kmatjuhi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 13:52:24 by kmatjuhi          #+#    #+#             */
/*   Updated: 2024/04/20 19:26:22 by kmatjuhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	init_struct(int argc, t_struct *p)
{
	int	i;

	i = -1;
	while (++i < p->nr_philos)
	{
		p->philos[i].x = i + 1;
		p->philos[i].die = p->die;
		p->philos[i].eat = p->eat;
		p->philos[i].sleep = p->sleep;
		p->philos[i].d_flag = &p->dead_flag;
		p->philos[i].time_last_meal = time_in_ms();
		if (argc == 6)
			p->philos[i].times_eat = p->times_eat;
		else
			p->philos[i].times_eat = -1;
	}
	return (1);
}

static int	init_mutex(t_struct *p)
{
	int	i;

	i = -1;
	p->forks = malloc((p->nr_philos + 1) * sizeof(pthread_mutex_t));
	if (!p->forks)
		return (1);
	while (++i <= p->nr_philos)
	{
		if (pthread_mutex_init(&(p->forks[i]), NULL) != 0)
		{
			free(p->forks);
			return (0);
		}
	}
	i = -1;
	while (++i < p->nr_philos)
	{
		p->philos[i].lock = &p->forks[p->nr_philos];
		p->philos[i].l_fork = &p->forks[i];
		if (i == p->nr_philos - 1)
			p->philos[p->nr_philos - 1].r_fork = &(p->forks[0]);
		else
			p->philos[i].r_fork = &p->forks[i + 1];
	}
	return (1);
}

int	init(int argc, t_struct *p)
{
	if (!init_mutex(p))
	{
		free(p->philos);
		return (0);
	}
	if (!init_struct(argc, p))
		return (0);
	return (1);
}
