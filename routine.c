/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmatjuhi <kmatjuhi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 14:42:29 by kmatjuhi          #+#    #+#             */
/*   Updated: 2024/04/17 10:39:44 by kmatjuhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_eat(t_philo *philo)
{
	if (*(philo->d_flag) != -1)
		return ;
	if ((time_in_ms() - philo->time_last_meal) > philo->die)
	{
		printf("%ld %d died\n", time_in_ms(), philo->x);
		philo->d_flag[0] = philo->x;
		return ;
	}
	pthread_mutex_lock(philo->l_fork);
	pthread_mutex_lock(philo->r_fork);
	printf("%ld %d has taken a fork\n", time_in_ms(), philo->x);
	printf("%ld %d has taken a fork\n", time_in_ms(), philo->x);
	printf("%ld %d is eating\n", time_in_ms(), philo->x);
	philo->time_last_meal = time_in_ms();
	if (philo->times_eat != -1)
		philo->times_eat--;
	usleep (philo->eat * 1000);
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
}

void	ft_sleep(t_philo *philo)
{
	if (*(philo->d_flag) != -1)
		return ;
	printf("%ld %d is sleeping\n", time_in_ms(), philo->x);
	usleep(philo->sleep * 1000);
}

void	ft_think(t_philo *philo)
{
	if (*(philo->d_flag) != -1)
		return ;
	printf("%ld %d is thinking\n", time_in_ms(), philo->x);
}