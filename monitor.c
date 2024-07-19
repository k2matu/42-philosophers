/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmatjuhi <kmatjuhi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 10:53:55 by kmatjuhi          #+#    #+#             */
/*   Updated: 2024/07/18 22:21:39 by kmatjuhi         ###   ########.fr       */
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
			return (FALSE);
		}
		pthread_mutex_unlock(philo->meal_lock);
		pthread_mutex_lock(philo->write_lock);
		printf("%lld %d died\n", time_in_ms() - philo->time_start, philo->x);
		pthread_mutex_lock(philo->dead_lock);
		philo->d_flag[0] = philo->x;
		pthread_mutex_unlock(philo->dead_lock);
		pthread_mutex_unlock(philo->write_lock);
		return (FALSE);
	}
	pthread_mutex_unlock(philo->meal_lock);
	return (TRUE);
}

static int	check_ate(t_philo *philo)
{
	if (philo->times_eat == -1)
		return (TRUE);
	if (philo->times_eat == 0)
		return (FALSE);
	return (TRUE);
}

static int	check_ate_all(t_struct *p)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (i < p->nr_philos)
	{
		if (!(check_ate(&p->philos[i])))
			count++;
		i++;
	}
	if (i == count)
	{
		pthread_mutex_lock(&p->write_lock);
		pthread_mutex_lock(&p->dead_lock);
		p->dead_flag = 1;
		pthread_mutex_unlock(&p->dead_lock);
		pthread_mutex_unlock(&p->write_lock);
		return (TRUE);
	}
	return (FALSE);
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
			if (!(check_death(&p->philos[i])))
				return (NULL);
			i++;
		}
		if (check_ate_all(p))
			return (NULL);
	}
	return (NULL);
}
