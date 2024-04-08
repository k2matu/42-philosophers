/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tread.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmatjuhi <kmatjuhi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 13:36:31 by kmatjuhi          #+#    #+#             */
/*   Updated: 2024/04/08 10:33:42 by kmatjuhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	*monitor(void *args)
{
	int i = 1;
	t_struct	*p = (t_struct *)args;
	while (p->philos[i].times_eat != 0)
	{
		printf("Hello from %x has left times to eat %ld\n", p->philos[i].x, p->philos[i].times_eat);
		i++;
		if (i == p->nr_philos)
			i = 1;
	}
	return (NULL);
}

static void	*routine(void *args)
{
	// routine should go around until the times eat is fullfilled or the philosopher dies.
	t_philo *philo = (t_philo *)args;
	// printf("Hello from %x has left times to eat %ld\n", philo->x, philo->times_eat);
	while (philo->times_eat != 0)
	{
		// printf("Hello from %x has left times to eat %ld\n", philo->x, philo->times_eat);
		philo->times_eat--;
	}
	return (NULL); 
}

int	tread(t_struct p)
{
	int			i;
	int			*res;
	pthread_t	th_monitor;

	i = 0;
	if (pthread_create(&th_monitor, NULL, &monitor, (void *)&p) != 0)
		return (1);
	while (i < p.nr_philos)
	{
		if (pthread_create(&p.philos[i + 1].th, NULL, &routine, (void *)&p.philos[i + 1]) != 0)
			return (1);
		i++;
	}
	i = 0;
	// take return value and check if its dead filosopher or end of meal. 
	if (pthread_join(th_monitor, (void **) &res) != 0)
		return (1);
	while (i < p.nr_philos)
	{
		if (pthread_join(p.philos[i + 1].th, (void **) &res) != 0)
			return (1);
		i++;
	}
	return (0);
}
