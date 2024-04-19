/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msg.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmatjuhi <kmatjuhi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 13:14:28 by kmatjuhi          #+#    #+#             */
/*   Updated: 2024/04/19 12:02:38 by kmatjuhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	print_msg(t_philo *philo, const char *msg)
{
	// printf("inside msg for %d\n", philo->x);
	pthread_mutex_lock(philo->lock);
	// printf("inside msg for locked%d\n", philo->x);
	if ((time_in_ms() - philo->time_last_meal) > philo->die)
	{
		if (philo->times_eat == 0 || philo->d_flag[0] != -1)
		{
			printf("somebody already died, inside %d\n", philo->x);
			pthread_mutex_unlock(philo->lock);
			return (0);
		}
		printf("1. %ld %d died\n", time_in_ms(), philo->x);
		philo->d_flag[0] = philo->x;
		pthread_mutex_unlock(philo->lock);
		// printf("unlocking and exiting for %d\n", philo->x);
		return (0);
	}
	if (philo->times_eat == 0 || philo->d_flag[0] != -1)
	{
		pthread_mutex_unlock(philo->lock);
		// printf("inside msg for unlocked 1 %d\n", philo->x);
		return (0);
	}
	printf("%ld %d %s\n", time_in_ms(), philo->x, msg);
	pthread_mutex_unlock(philo->lock);
	// printf("inside msg for unlocked 2 %d\n", philo->x);
	return (1);
}
