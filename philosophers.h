/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmatjuhi <kmatjuhi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 11:54:25 by kmatjuhi          #+#    #+#             */
/*   Updated: 2024/04/05 18:15:29 by kmatjuhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>

typedef struct s_philo
{
	pthread_t	th;
	int			x;
	int			fork;
	long		die;
	long		eat;
	long		sleep;
	long		times_eat;
	int			d_flag;
}	t_philo;

typedef struct s_struct
{
	t_philo	*philos;
	int		nr_philos;
}	t_struct;

long	time_in_ms(void);
long	atol(const char *str);
void	print_msg(int x, const char *msg);
int		tread(t_struct p);

#endif