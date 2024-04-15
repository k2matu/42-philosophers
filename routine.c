/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmatjuhi <kmatjuhi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 14:42:29 by kmatjuhi          #+#    #+#             */
/*   Updated: 2024/04/11 06:33:20 by kmatjuhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->l_fork);
	printf("%ld %d has taken a fork\n", time_in_ms(), philo->x);
	pthread_mutex_lock(philo->r_fork);
	printf("%ld %d has taken a fork\n", time_in_ms(), philo->x);
	printf("%ld %d is eating\n", time_in_ms(), philo->x);
	usleep (philo->eat * 1000);
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
	printf("%ld %d is done eating and put down the forks\n", time_in_ms(), philo->x);
}

void	ft_sleep(t_philo *philo)
{
	printf("%ld %d is sleeping\n", time_in_ms(), philo->x);
	usleep(philo->sleep * 1000);
}

void	ft_think(t_philo *philo)
{
	printf("%ld %d is thinking\n", time_in_ms(), philo->x);
}
