/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tread.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmatjuhi <kmatjuhi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 13:36:31 by kmatjuhi          #+#    #+#             */
/*   Updated: 2024/04/04 13:57:50 by kmatjuhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	*eat(void *arg)
{
	int x = *(int*)arg;
	printf("philosopther nr %d\n", x);
}

int	tread(t_struct p)
{
	pthread_t	*th;
	int			i;

	i = 0;
	while (i < p.nr_philos)
	{
		if (pthread_create(&th[i], NULL, &eat, (void *)&p.philos[i + 1]) != 0)
			return (1);
		i++;
	}
	i = 0;
	while (i < p.nr_philos)
	{
		if (pthread_join(th[i], NULL) != 0)
			return (1);
		i++;
	}
	return (0);
}
