/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmatjuhi <kmatjuhi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 11:54:25 by kmatjuhi          #+#    #+#             */
/*   Updated: 2024/04/18 09:38:17 by kmatjuhi         ###   ########.fr       */
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
	pthread_t		th;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t *lock;
	int				x;
	int				fork;
	long			die;
	long			eat;
	long			sleep;
	long			times_eat;
	long			time_last_meal;
	int				*d_flag;
}	t_philo;

typedef struct s_struct
{
	t_philo			*philos;
	pthread_mutex_t	*forks;
	int				nr_philos;
	int				dead_flag;
}	t_struct;

long		time_in_ms(void);
long		atol(const char *str);
int			print_msg(t_philo *philo, const char *msg);
int			tread(t_struct *p);
t_struct	*init_struct(int argc, char **argv, t_struct *p);
int			init_mutex(t_struct *p);
int			ft_eat(t_philo *philo);
int			ft_sleep(t_philo *philo);
int			ft_think(t_philo *philo);

#endif