/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tread.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmatjuhi <kmatjuhi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 13:36:31 by kmatjuhi          #+#    #+#             */
/*   Updated: 2024/07/18 11:11:50 by kmatjuhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	join_threads(t_struct *p, pthread_t monitor, int threads)
{
	int	i;

	i = 0;
	if (pthread_join(monitor, NULL) != 0)
		return (error_msg("Pthread join failed", 0));
	while (i < threads)
	{
		if (pthread_join(p->philos[i].th, NULL) != 0)
			return (error_msg("Pthread join failed", 0));
		i++;
	}
	return (1);
}

int	tread(t_struct *p)
{
	pthread_t	monitor;
	int			i;
	int			code;

	i = 0;
	if (pthread_create(&monitor, NULL, &monitoring, p) != 0)
		return (error_msg("Pthread create failed", 0));
	while (i < p->nr_philos)
	{
		if (pthread_create(&p->philos[i].th, NULL, \
		&routine, (void *)&p->philos[i]) != 0)
		{
			code = error_msg("Pthread create failed", 0);
			break ;
		}
		i++;
	}
	if (join_threads(p, monitor, i) == 0)
		return (0);
	if (code == 0)
		return (0);
	return (1);
}
