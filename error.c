/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmatjuhi <kmatjuhi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 10:52:34 by kmatjuhi          #+#    #+#             */
/*   Updated: 2024/07/18 14:41:46 by kmatjuhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	error_msg(char *str, int exit_code)
{
	printf("%s\n", str);
	return (exit_code);
}

void	cleanup_resources(t_struct *p, int i)
{
	if (p->forks)
	{
		while (--i >= 0)
		{
			pthread_mutex_destroy(&p->forks[i]);
		}
		free(p->forks);
	}
	free(p->philos);
}
