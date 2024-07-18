/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmatjuhi <kmatjuhi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 10:53:55 by kmatjuhi          #+#    #+#             */
/*   Updated: 2024/07/18 11:07:30 by kmatjuhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	checker(t_philo *philo)
{
	pthread_mutex_lock(philo->lock);
	if ((time_in_ms() - philo->time_last_meal) > philo->die)
	{
		if (philo->times_eat == 0 || philo->d_flag[0] != -1)
		{
			pthread_mutex_unlock(philo->lock);
			return (0);
		}
		printf("%ld %d died\n", time_in_ms() - philo->time_start, philo->x);
		philo->d_flag[0] = philo->x;
		pthread_mutex_unlock(philo->lock);
		return (0);
	}
	pthread_mutex_unlock(philo->lock);
	return (1);
}

void	*monitoring(void *args)
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
