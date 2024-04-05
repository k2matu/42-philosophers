/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tread.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmatjuhi <kmatjuhi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 13:36:31 by kmatjuhi          #+#    #+#             */
/*   Updated: 2024/04/05 18:19:28 by kmatjuhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	*routine(void *arg)
{
	// routine should go around until the times eat is fullfilled or the philosopher dies. 
	t_philo *philo = (t_philo *)arg;
	printf("philosopther nr %d\n ", philo->x);
	
	return (NULL);
}

int	tread(t_struct p)
{
	int			i;

	i = 0;
	while (i < p.nr_philos)
	{
		if (pthread_create(&p.philos[i + 1].th, NULL, &routine, (void *)&p.philos[i + 1]) != 0)
			return (1);
		printf("%d\n", p.philos[i + 1].x);
		i++;
	}
	i = 0;
	while (i < p.nr_philos)
	{
		// take return value and check if its dead filosopher or end of meal. 
		if (pthread_join(p.philos[i + 1].th, NULL) != 0)
			return (1);
		i++;
	}
	return (0);
}
