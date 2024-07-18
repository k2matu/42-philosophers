/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmatjuhi <kmatjuhi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 10:53:55 by kmatjuhi          #+#    #+#             */
/*   Updated: 2024/07/18 15:19:03 by kmatjuhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	check_death(t_philo *philo)
{
	pthread_mutex_lock(philo->meal_lock);
	if ((time_in_ms() - philo->time_last_meal) > philo->die)
	{
		if (philo->d_flag[0] != -1)
		{
			pthread_mutex_unlock(philo->meal_lock);
			return (0);
		}
		pthread_mutex_unlock(philo->meal_lock);
		pthread_mutex_lock(philo->write_lock);
		printf("%ld %d died\n", time_in_ms() - philo->time_start, philo->x);
		pthread_mutex_unlock(philo->write_lock);
		pthread_mutex_lock(philo->dead_lock);
		philo->d_flag[0] = philo->x;
		pthread_mutex_unlock(philo->dead_lock);
		return (0);
	}
	pthread_mutex_unlock(philo->meal_lock);
	return (1);
}

static int	check_ate(t_philo *philo)
{
	if (philo->times_eat == -1)
		return (1);
	if (philo->times_eat == 0)
		return (0);
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
			if (!(check_death(&p->philos[i])) || !(check_ate(&p->philos[i])))
				return (NULL);
			i++;
		}
	}
	return (NULL);
}
