/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tread.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmatjuhi <kmatjuhi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 13:36:31 by kmatjuhi          #+#    #+#             */
/*   Updated: 2024/04/16 08:43:56 by kmatjuhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	*monitor(void *args)
{
	int i = 0;
	t_struct	*p = (t_struct *)args;
	while (p->philos[i].times_eat != 0 && p->philos[i].d_flag != 1)
	{
		printf("Hello from %x has left times to eat %ld\n", p->philos[i].x, p->philos[i].times_eat);
		i++;
		if (i == p->nr_philos - 1)
			i = 0;
	}
	return (NULL);
}

static void	*routine(void *args)
{
	t_philo *philo = (t_philo *)args;

	while (philo->times_eat != 0 && philo->d_flag == 0)
	{
		ft_eat(philo);
		philo->times_eat--;
		ft_sleep(philo);
		ft_think(philo);
	}
	return (NULL);
}

int	tread(t_struct *p)
{
	int			i;
	int			*res;
	pthread_t	th_monitor;

	i = 0;
	if (pthread_create(&th_monitor, NULL, &monitor, (void *)&p) != 0)
		return (1);
	while (i < p->nr_philos)
	{
		if (pthread_create(&p->philos[i].th, NULL, &routine, (void *)&p->philos[i]) != 0)
			return (1);
		i++;
	}
	i = 0;
	if (pthread_join(th_monitor, (void **) &res) != 0)
		return (1);
	while (i < p->nr_philos)
	{
		if (pthread_join(p->philos[i].th, (void **) &res) != 0)
			return (1);
		i++;
	}
	return (0);
}
