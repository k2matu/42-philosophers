/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmatjuhi <kmatjuhi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 14:42:29 by kmatjuhi          #+#    #+#             */
/*   Updated: 2024/07/18 22:34:37 by kmatjuhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	ft_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->r_fork);
	pthread_mutex_lock(philo->l_fork);
	print_msg(philo, "has taken a fork");
	print_msg(philo, "has taken a fork");
	print_msg(philo, "is eating");
	pthread_mutex_lock(philo->meal_lock);
	philo->time_last_meal = time_in_ms();
	pthread_mutex_unlock(philo->meal_lock);
	ft_usleep (philo, philo->eat);
	pthread_mutex_lock(philo->meal_lock);
	if (philo->times_eat > 0)
		philo->times_eat--;
	pthread_mutex_unlock(philo->meal_lock);
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_unlock(philo->l_fork);
}

static void	ft_sleep(t_philo *philo)
{
	print_msg(philo, "is sleeping");
	ft_usleep(philo, philo->sleep);
}

static void	ft_think(t_philo *philo)
{
	print_msg(philo, "is thinking");
}

int	dead_philo(t_philo *philo)
{
	pthread_mutex_lock(philo->dead_lock);
	if (philo->d_flag[0] != -1)
	{
		pthread_mutex_unlock(philo->dead_lock);
		return (TRUE);
	}
	pthread_mutex_unlock(philo->dead_lock);
	return (FALSE);
}

void	*routine(void *args)
{
	t_philo	*philo;

	philo = (t_philo *)args;
	if (philo->nr_philos == 1)
	{
		printf("%lld 1 has taken a fork\n", time_in_ms() - time_in_ms());
		usleep(philo->die * 1000);
		printf("%lld 1 died\n", time_in_ms() - philo->time_last_meal);
		return (NULL);
	}
	if (philo->x % 2 == 0)
	{
		ft_think(philo);
		ft_usleep(philo, philo->eat / 2);
	}
	while (!dead_philo(philo) && philo->times_eat != 0)
	{
		ft_eat(philo);
		if (philo->times_eat == 0)
			return (NULL);
		ft_sleep(philo);
		ft_think(philo);
	}
	return (NULL);
}
