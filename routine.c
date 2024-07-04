/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmatjuhi <kmatjuhi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 14:42:29 by kmatjuhi          #+#    #+#             */
/*   Updated: 2024/07/04 13:09:19 by kmatjuhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_usleep(t_philo *philo, long time)
{
	long	start;
	long	new_time;

	start = time_in_ms();
	new_time = time_in_ms();
	if ((start + time) - philo->time_last_meal > (philo->die))
	{
		printf("%ld %d died\n", philo->time_last_meal + philo->die, philo->x);
		philo->d_flag[0] = philo->x;
		return (0);
	}
	while ((time + start) > new_time)
	{
		usleep(1000);
		new_time = time_in_ms();
	}
	return (1);
}

int	ft_eat(t_philo *philo)
{
	if (*(philo->d_flag) != -1)
		return (0);
	pthread_mutex_lock(philo->l_fork);
	pthread_mutex_lock(philo->r_fork);
	if (!print_msg(philo, "has taken a fork") \
	|| !print_msg(philo, "has taken a fork") \
	|| !print_msg(philo, "is eating"))
	{
		pthread_mutex_unlock(philo->l_fork);
		pthread_mutex_unlock(philo->r_fork);
		return (0);
	}
	philo->time_last_meal = time_in_ms();
	if (philo->times_eat != -1)
		philo->times_eat--;
	if (!ft_usleep (philo, philo->eat))
	{
		pthread_mutex_unlock(philo->l_fork);
		pthread_mutex_unlock(philo->r_fork);
		return (0);
	}
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
	if (!ft_usleep(philo, philo->sleep))
		return (0);
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
