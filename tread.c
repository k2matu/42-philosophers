/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tread.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmatjuhi <kmatjuhi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 13:36:31 by kmatjuhi          #+#    #+#             */
/*   Updated: 2024/07/15 09:46:41 by kmatjuhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	*routine(void *args)
{
	t_philo	*philo;

	philo = (t_philo *)args;
	if (philo->x % 2 == 0)
		usleep(10);
	if (philo->nr_philos == 1)
	{
		printf("%ld 1 has taken a fork\n", time_in_ms() - time_in_ms());
		usleep(philo->die * 1000);
		printf("%ld 1 died\n", time_in_ms() - philo->time_last_meal);
		return (NULL);
	}
	while (philo->times_eat != 0 && philo->d_flag[0] == -1)
	{
		if (ft_eat(philo) == 0)
			return (NULL);
		if (ft_sleep(philo) == 0)
			return (NULL);
		if (ft_think(philo) == 0)
			return (NULL);
	}
	return (NULL);
}

int	checker(t_philo *philo)
{
	if ((time_in_ms() - philo->time_last_meal) > philo->die)
	{
		if (philo->times_eat == 0 || philo->d_flag[0] != -1)
			return (0);
		printf("%ld %d died\n", time_in_ms() - philo->time_start, philo->x);
		philo->d_flag[0] = philo->x;
		return (0);
	}
	return (1);
}

static void	*monitoring(void *args)
{
	t_struct	*p;
	int			i;

	p = (t_struct *)args;
	if (p->nr_philos == 1)
		return (NULL);
	while (1)
	{
		i = 0;
		while (i < p->nr_philos)
		{
			if (!(checker(&p->philos[i])))
				return (NULL);
			i++;
		}
	}
	return (NULL);
}

int	tread(t_struct *p)
{
	pthread_t	monitor;
	int			i;

	i = 0;
	if (pthread_create(&monitor, NULL, &monitoring, p) != 0)
		return (error_msg("Pthread create failed", 0));
	while (i < p->nr_philos)
	{
		if (pthread_create(&p->philos[i].th, NULL, \
		&routine, (void *)&p->philos[i]) != 0)
			return (error_msg("Pthread create failed", 0));
		i++;
	}
	i = 0;
	if (pthread_join(monitor, NULL) != 0)
		return (error_msg("Pthread join failed", 0));
	while (i < p->nr_philos)
	{
		if (pthread_join(p->philos[i].th, NULL) != 0)
			return (error_msg("Pthread join failed", 0));
		i++;
	}
	return (1);
}
