/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmatjuhi <kmatjuhi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 12:36:46 by kmatjuhi          #+#    #+#             */
/*   Updated: 2024/07/18 21:19:48 by kmatjuhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long long	time_in_ms(void)
{
	struct timeval	te;
	long long		millisec;

	gettimeofday(&te, NULL);
	millisec = te.tv_sec * 1000LL + te.tv_usec / 1000;
	return (millisec);
}

void	ft_usleep(t_philo *philo, long long time)
{
	long long	start;
	long long	new_time;

	start = time_in_ms();
	new_time = time_in_ms();
	while ((time + start) > new_time)
	{
		usleep(1000);
		if (dead_philo(philo))
			return ;
		new_time = time_in_ms();
	}
}
