/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tread.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmatjuhi <kmatjuhi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 13:36:31 by kmatjuhi          #+#    #+#             */
/*   Updated: 2024/04/05 19:08:38 by kmatjuhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	*routine(void *arg)
{
	// routine should go around until the times eat is fullfilled or the philosopher dies. 
	t_philo *philo = (t_philo *)arg;
	while (philo->x != 3)
		printf("philosopther nr %d and eat %ld\n", philo->x, philo->eat);
	if (philo->x == 3)
		return (NULL);
}

int	tread(t_struct p)
{
	int	i;
	int *res;

	i = 0;
	while (res != NULL)
	{
		while (i < p.nr_philos)
		{
			if (pthread_create(&p.philos[i + 1].th, NULL, &routine, (void *)&p.philos[i + 1]) != 0)
				return (1);
			i++;
		}
		i = 0;
		while (i < p.nr_philos)
		{
			// take return value and check if its dead filosopher or end of meal. 
			if (pthread_join(p.philos[i + 1].th, (void **) &res) != 0)
				return (1);
			i++;
		}
		
	}
		if (res == NULL)
		{
			printf("it was number 3\n");
			i = 0;
			while (i < p.nr_philos)
			{
				pthread_detach(p.philos[i + 1].th);
				i++;
			}
		}
	return (0);
}
