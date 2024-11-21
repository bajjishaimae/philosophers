/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbajji <cbajji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 18:07:02 by cbajji            #+#    #+#             */
/*   Updated: 2024/11/21 17:00:46 by cbajji           ###   ########.fr       */
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
	int				id;
	pthread_t		thread;
	long long		last_meal_time;
	int				meals_eaten;
	int				flag;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	lock_lasttime;
	pthread_mutex_t	lock_nmeals;
	struct s_data	*data;
}	t_philo;

typedef struct s_data
{
	long long		start_time;
	int				time_to_eat;
	int				time_to_die;
	int				time_to_sleep;
	int				numberof_philos;
	int				numberof_meals;
	int				is_alive;
	int				philos_full;
	pthread_mutex_t	print;
	pthread_mutex_t	check_death;
	pthread_mutex_t	check_full;
	t_philo			*philosophers;
	pthread_mutex_t	*forks;
}	t_data;

typedef struct s_cleanup_state
{
	int				forks_initialized;
	int				philos_initialized;
	int				data_mutex_initialized;
}	t_cleanup_state;

void		*supervisor(void *data_void);
long long	get_time(void);
int			parse(int ac, char **av, t_data *data, int i);
void		print_status(t_philo *philo, char status);
void		create_super_thread(t_data *data);
void		*routine(void *philo_void);
int			get_check_death(t_philo *philo);
void		set_check_death(t_philo *philo, int value);
int			get_check_full(t_philo *philo);
void		set_check_full(t_philo *philo);
void		set_lasttime(t_philo *philo);
long long	get_lasttime(t_philo *philo);
void		set_nmeals(t_philo *philo);
int			get_nmeals(t_philo *philo);
int			ft_atoi(const char *str);
void		safe_mutex_destroy(pthread_mutex_t *mutex, char *name);
void		cleanup(t_data *data, t_cleanup_state *state);
void		create_threads(t_data *data);
int			ft_usleep(size_t milliseconds, t_philo *philo);
#endif
