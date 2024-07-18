/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmatjuhi <kmatjuhi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 11:54:25 by kmatjuhi          #+#    #+#             */
/*   Updated: 2024/07/18 15:05:03 by kmatjuhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>

typedef struct s_philo
{
	pthread_t		th;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*write_lock;
	pthread_mutex_t	*meal_lock;
	pthread_mutex_t	*dead_lock;
	int				nr_philos;
	int				x;
	int				*left_eating;
	int				*right_eating;
	int				fork;
	long			die;
	long			eat;
	long			sleep;
	long			times_eat;
	long			time_last_meal;
	long			time_start;
	int				*d_flag;
}	t_philo;

typedef struct s_struct
{
	t_philo			*philos;
	pthread_mutex_t	*forks;
	pthread_mutex_t	write_lock;
	pthread_mutex_t	meal_lock;
	pthread_mutex_t	dead_lock;
	int				nr_philos;
	long			die;
	long			eat;
	long			sleep;
	long			times_eat;
	int				dead_flag;
}	t_struct;

void	*monitoring(void *args);
void	*routine(void *args);
void	cleanup_resources(t_struct *p, int i);
long	time_in_ms(void);
long	p_atol(const char *str);
void	print_msg(t_philo *philo, const char *msg);
int		tread(t_struct *p);
int		init(int argc, t_struct *p);
int		error_msg(char *str, int exit_code);
void	ft_usleep(t_philo *philo, long time);
int		dead_philo(t_philo *philo);

#endif