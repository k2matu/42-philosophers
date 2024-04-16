/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmatjuhi <kmatjuhi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 11:54:25 by kmatjuhi          #+#    #+#             */
/*   Updated: 2024/04/16 10:49:39 by kmatjuhi         ###   ########.fr       */
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
	int				x;
	int				fork;
	long			die;
	long			eat;
	long			sleep;
	long			times_eat;
	long			time_last_meal;
	int				d_flag;
}	t_philo;

typedef struct s_struct
{
	t_philo	*philos;
	int		nr_philos;
	pthread_mutex_t *forks;
}	t_struct;

long		time_in_ms(void);
long		atol(const char *str);
void		print_msg(int x, const char *msg);
int			tread(t_struct *p);
t_struct	*init_struct(int argc, char **argv, t_struct *p);
int			init_mutex(t_struct *p);
void		ft_eat(t_philo *philo);
void		ft_sleep(t_philo *philo);
void		ft_think(t_philo *philo);

#endif