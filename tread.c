/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tread.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmatjuhi <kmatjuhi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 13:36:31 by kmatjuhi          #+#    #+#             */
/*   Updated: 2024/04/18 09:47:26 by kmatjuhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	*routine(void *args)
{
	t_philo	*philo;

	philo = (t_philo *)args;
	while (philo->times_eat != 0 && philo->d_flag[0] == -1)
	{
		if (ft_eat(philo) == 0)
			return (NULL);
		if (ft_sleep(philo) == 0)
			return (NULL);
		if (ft_think(philo) == 0)
			return (NULL);


	}
	return (NULL);
}

int	tread(t_struct *p)
{
	int	i;

	i = 0;
	while (i < p->nr_philos)
	{
		if (pthread_create(&p->philos[i].th, NULL, \
		&routine, (void *)&p->philos[i]) != 0)
			return (1);
		i++;
	}
	i = 0;
	while (i < p->nr_philos)
	{
		if (pthread_join(p->philos[i].th, NULL) != 0)
			return (1);
		i++;
	}
	return (0);
}
