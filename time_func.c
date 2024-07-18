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

long	time_in_ms(void)
{
	struct timeval	te;
	long			millisec;

	gettimeofday(&te, NULL);
	millisec = te.tv_sec * 1000LL + te.tv_usec / 1000;
	return (millisec);
}

void	ft_usleep(long time)
{
	long	start;
	long	new_time;

	start = time_in_ms();
	new_time = time_in_ms();
	while ((time + start) > new_time)
	{
		usleep(1000);
		new_time = time_in_ms();
	}
}
