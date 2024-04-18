/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmatjuhi <kmatjuhi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 14:42:29 by kmatjuhi          #+#    #+#             */
/*   Updated: 2024/04/18 10:56:16 by kmatjuhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_eat(t_philo *philo)
{
	if (*(philo->d_flag) != -1)
		return (0);
	if ((time_in_ms() - philo->time_last_meal) > philo->die)
	{
		pthread_mutex_lock(philo->lock);
		if (philo->times_eat == 0 || philo->d_flag[0] != -1)
		{
			pthread_mutex_unlock(philo->lock);
			return (0);
		}
		printf("%ld %d died\n", time_in_ms(), philo->x);
		philo->d_flag[0] = philo->x;
		pthread_mutex_unlock(philo->lock);
		return (0);
	}
	pthread_mutex_lock(philo->l_fork);
	if (print_msg(philo, "has taken a fork") == 0)
	{
		pthread_mutex_unlock(philo->l_fork);
		return (0);
	}
	pthread_mutex_lock(philo->r_fork);
	if (print_msg(philo, "has taken a fork") == 0)
	{
		pthread_mutex_unlock(philo->l_fork);
		pthread_mutex_unlock(philo->r_fork);
		return (0);
	}
	if (print_msg(philo, "is eating") == 0)
	{
		pthread_mutex_unlock(philo->l_fork);
		pthread_mutex_unlock(philo->r_fork);
		return (0);
	}
	philo->time_last_meal = time_in_ms();
	if (philo->times_eat != -1)
		philo->times_eat--;
	usleep (philo->eat * 1000);
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
	return (1);
}

int	ft_sleep(t_philo *philo)
{
	if (*(philo->d_flag) != -1)
		return (0);
	if (print_msg(philo, "is sleeping") == 0)
		return (0);
	usleep(philo->sleep * 1000);
	return (1);
}

int	ft_think(t_philo *philo)
{
	if (*(philo->d_flag) != -1)
		return (0);
	if (print_msg(philo, "is thinking") == 0) 
		return (0);
	return (1);
}
