/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbajji <cbajji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 11:18:36 by cbajji            #+#    #+#             */
/*   Updated: 2024/11/21 16:49:48 by cbajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	create_threads(t_data *data)
{
	int	i;

	i = 0;
	data->start_time = get_time(); //TODO check it
	while (i < data->numberof_philos)
	{
		if (pthread_create(&data->philosophers[i].thread, NULL, routine,
				(void *)&data->philosophers[i]) != 0)
			return ;
		i++;
	}
	create_super_thread(data);
	i = 0;
	while (i < data->numberof_philos)
	{
		if (pthread_join(data->philosophers[i].thread, NULL) != 0)
			return ;
		i++;
	}
}

void	print_status(t_philo *philo, char status)
{
	// long long time = get_time();
	
	if (!get_check_death(philo) || get_check_full(philo) == philo->data->numberof_philos)
		return ;
	pthread_mutex_lock(&philo->data->print);
	if (!get_check_death(philo))
	{
		pthread_mutex_unlock(&philo->data->print);
		return ;
	}
	if (status == 'r')
	{
		printf ("%lld %d has taken a right fork\n", get_time()
			- philo->data->start_time, philo->id);
		if (!get_check_death(philo))
		{
			pthread_mutex_unlock(&philo->data->print);
			return ;	
		}
	}
	else if (status == 'l')
	{
		printf ("%lld %d has taken a left fork\n", get_time()
			- philo->data->start_time, philo->id);
		if (!get_check_death(philo))
		{
			pthread_mutex_unlock(&philo->data->print);
			return ;		
		}
	}
	else if (status == 'e')
	{
		printf ("%lld %d is eating\n", get_time()
			- philo->data->start_time, philo->id);
		if (!get_check_death(philo))
		{
			pthread_mutex_unlock(&philo->data->print);
			return ;
		}
	}
	else if (status == 's')
	{
		printf ("%lld %d is sleeping\n", get_time()
			- philo->data->start_time, philo->id);
		if (!get_check_death(philo))
		{
			pthread_mutex_unlock(&philo->data->print);
			return ;
		}
	}
	else if (status == 't')
	{
		printf ("%lld %d is thinking\n", get_time()
			- philo->data->start_time, philo->id);
	}
	pthread_mutex_unlock(&philo->data->print);
}

void	eating(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	print_status(philo, 'l');
	pthread_mutex_lock(philo->right_fork);
	print_status(philo, 'r');
	print_status(philo, 'e');
	set_lasttime(philo);
	ft_usleep(philo->data->time_to_eat, philo);
	set_nmeals(philo);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	*routine(void *philo_void)
{
	t_philo	*philo;

	philo = (t_philo *)philo_void;
	if (philo->data->numberof_philos == 1)
	{
		print_status(philo, 'l');
		return (NULL);
	}
	if (philo->id % 2 == 0)
		usleep(100);
		// ft_usleep(philo->data->time_to_eat, philo);
	while (1)
	{
		eating(philo);
		if (!get_check_death(philo))
			break;
		print_status(philo, 's');
		ft_usleep(philo->data->time_to_sleep, philo);
		if (!get_check_death(philo))
			break;
		print_status(philo, 't');
		if (philo->data->numberof_meals != -1
			&& get_nmeals(philo) == philo->data->numberof_meals)
		{
			break ;
		}
		if (!get_check_death(philo))
			break;
	}
	return (NULL);
}
