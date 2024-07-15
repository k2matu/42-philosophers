/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_msg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmatjuhi <kmatjuhi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 10:52:34 by kmatjuhi          #+#    #+#             */
/*   Updated: 2024/07/15 09:14:25 by kmatjuhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	error_msg(char *str, int exit_code)
{
	printf("%s\n", str);
	return (exit_code);
}

void	cleanup_resources(t_struct *p)
{
	int	i;

	i = 0;
	if (p->forks)
	{
		while (i < p->nr_philos)
		{
			pthread_mutex_destroy(&p->forks[i]);
			i++;
		}
		free(p->forks);
	}
	free(p->philos);
}
