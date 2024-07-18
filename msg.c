/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msg.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmatjuhi <kmatjuhi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 13:14:28 by kmatjuhi          #+#    #+#             */
/*   Updated: 2024/07/18 21:26:50 by kmatjuhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	print_msg(t_philo *philo, const char *msg)
{
	pthread_mutex_lock(philo->write_lock);
	if (!dead_philo(philo))
		printf("%ld %d %s\n", time_in_ms() - philo->time_start, philo->x, msg);
	pthread_mutex_unlock(philo->write_lock);
}
