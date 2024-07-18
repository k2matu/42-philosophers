/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmatjuhi <kmatjuhi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 14:42:29 by kmatjuhi          #+#    #+#             */
/*   Updated: 2024/07/18 11:14:05 by kmatjuhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	lock_order(t_philo *philo)
{
	if (philo->l_fork < philo->r_fork)
	{
		pthread_mutex_lock(philo->l_fork);
		pthread_mutex_lock(philo->r_fork);
	}
	else
	{
		pthread_mutex_lock(philo->r_fork);
		pthread_mutex_lock(philo->l_fork);
	}
}

static int	ft_eat(t_philo *philo)
{
	lock_order(philo);
	if (!print_msg(philo, "has taken a fork") \
	|| !print_msg(philo, "has taken a fork") \
	|| !print_msg(philo, "is eating"))
	{
		pthread_mutex_unlock(philo->r_fork);
		pthread_mutex_unlock(philo->l_fork);
		return (0);
	}
	pthread_mutex_lock(philo->lock);
	pthread_mutex_unlock(philo->lock);
	if (!ft_usleep (philo, philo->eat))
	{
		pthread_mutex_unlock(philo->r_fork);
		pthread_mutex_unlock(philo->l_fork);
		return (0);
	}
	philo->time_last_meal = time_in_ms();
	if (philo->times_eat != -1)
		philo->times_eat--;
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_unlock(philo->l_fork);
	return (1);
}

static int	ft_sleep(t_philo *philo)
{
	if (print_msg(philo, "is sleeping") == 0)
		return (0);
	if (!ft_usleep(philo, philo->sleep))
		return (0);
	return (1);
}

static int	ft_think(t_philo *philo)
{
	if (print_msg(philo, "is thinking") == 0)
		return (0);
	return (1);
}

void	*routine(void *args)
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
	while (1)
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
