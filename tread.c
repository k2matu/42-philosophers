/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tread.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmatjuhi <kmatjuhi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 13:36:31 by kmatjuhi          #+#    #+#             */
/*   Updated: 2024/07/15 07:43:25 by kmatjuhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	*routine(void *args)
{
	t_philo	*philo;

	philo = (t_philo *)args;
	if (philo->x % 2 == 0)
		usleep(5);
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
	// pthread_mutex_lock(philo->lock);
	if ((time_in_ms() - philo->time_last_meal) > philo->die)
	{
		if (philo->times_eat == 0 || philo->d_flag[0] != -1)
		{
			// pthread_mutex_unlock(philo->lock);
			return (0);
		}
		printf("%ld %d died\n", time_in_ms() - philo->time_start, philo->x);
		philo->d_flag[0] = philo->x;
		// pthread_mutex_unlock(philo->lock);
		return (0);
	}
	// pthread_mutex_unlock(philo->lock);
	return (1);
}


static void	*monitoring(void *args)
{
	t_struct *p;
	int		i;

	p = (t_struct *)args;
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
	{
		free(p->philos);
		return (0);
	}
	while (i < p->nr_philos)
	{
		if (pthread_create(&p->philos[i].th, NULL, \
		&routine, (void *)&p->philos[i]) != 0)
		{
			free(p->philos);
			return (0);
		}
		i++;
	}
	i = 0;
	if (pthread_join(monitor, NULL) != 0)
	{
		free(p->philos);
		return (0);
	}
	while (i < p->nr_philos)
	{
		if (pthread_join(p->philos[i].th, NULL) != 0)
		{
			free(p->philos);
			return (0);
		}
		i++;
	}
	return (1);
}
