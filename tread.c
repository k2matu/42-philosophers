/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tread.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmatjuhi <kmatjuhi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 13:36:31 by kmatjuhi          #+#    #+#             */
/*   Updated: 2024/07/18 22:18:18 by kmatjuhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	join_threads(t_struct *p, pthread_t monitor, int threads)
{
	int	i;

	i = 0;
	if (pthread_join(monitor, NULL) != 0)
		return (error_msg("Pthread join failed", FALSE));
	while (i < threads)
	{
		if (pthread_join(p->philos[i].th, NULL) != 0)
			return (error_msg("Pthread join failed", FALSE));
		i++;
	}
	return (TRUE);
}

int	tread(t_struct *p)
{
	pthread_t	monitor;
	int			i;
	int			code;

	i = 0;
	if (pthread_create(&monitor, NULL, &monitoring, p) != 0)
		return (error_msg("Pthread create failed", FALSE));
	while (i < p->nr_philos)
	{
		if (pthread_create(&p->philos[i].th, NULL, \
		&routine, (void *)&p->philos[i]) != 0)
		{
			code = error_msg("Pthread create failed", FALSE);
			break ;
		}
		i++;
	}
	if (join_threads(p, monitor, i) == FALSE)
		return (FALSE);
	if (code == FALSE)
		return (FALSE);
	return (TRUE);
}
