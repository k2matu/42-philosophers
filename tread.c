/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tread.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmatjuhi <kmatjuhi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 13:36:31 by kmatjuhi          #+#    #+#             */
/*   Updated: 2024/04/17 10:40:58 by kmatjuhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	*routine(void *args)
{
	t_philo	*philo;

	philo = (t_philo *)args;
	while (philo->times_eat != 0 && philo->d_flag[0] == -1)
	{
		ft_eat(philo);
		if (philo->times_eat == 0 || philo->d_flag[0] != -1)
			return (NULL);
		ft_sleep(philo);
		if (philo->d_flag[0] != -1)
			return (NULL);
		ft_think(philo);
		if (philo->d_flag[0] != -1)
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
