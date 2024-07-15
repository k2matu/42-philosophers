/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msg.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmatjuhi <kmatjuhi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 13:14:28 by kmatjuhi          #+#    #+#             */
/*   Updated: 2024/07/15 00:23:33 by kmatjuhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	print_msg(t_philo *philo, const char *msg)
{
	pthread_mutex_lock(philo->lock);
	if (philo->times_eat == 0 || philo->d_flag[0] != -1)
	{
		pthread_mutex_unlock(philo->lock);
		return (0);
	}
	printf("%ld %d %s\n", time_in_ms() - philo->time_start, philo->x, msg);
	pthread_mutex_unlock(philo->lock);
	return (1);
}
