/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbajji <cbajji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 11:18:36 by cbajji            #+#    #+#             */
/*   Updated: 2024/10/23 10:12:16 by cbajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	case_one(t_philo *philo)
{
	pthread_mutex_lock(philo->lock);
	philo->last_meal_time = get_time();
	pthread_mutex_unlock(philo->lock);
	pthread_mutex_lock(philo->left_fork);
	print_status(philo, 'l');
}

void print_status(t_philo *philo, char status)
{
	
	pthread_mutex_lock(philo->data->check_death);
	printf("lock 1\n");
	pthread_mutex_lock(philo->data->check_full);
	printf("lock 2\n");
	if (!philo->data->is_alive
		|| philo->data->philos_full == philo->data->numberof_philos)
	{
		pthread_mutex_unlock(philo->data->check_death);
		printf("unlock 1\n");
		pthread_mutex_unlock(philo->data->check_full);
		printf("unlock 2\n");
		return ;
	}
	pthread_mutex_unlock(philo->data->check_death);
	printf("unlock 1\n");
	pthread_mutex_unlock(philo->data->check_full);
	printf("unlock 2\n");
	pthread_mutex_lock(philo->data->print);
	printf("lock 3\n");
	if (status == 'r')
		printf("%d takes the right fork\n", philo->id);
	else if (status == 'l')
		printf("%d takes the left fork\n", philo->id);
	else if (status == 'e')
		printf("%d is eating\n", philo->id);
	else if (status == 's')
		printf("%d is sleeping\n", philo->id);
	else if (status == 't')
		printf("%d is thinking\n", philo->id);
	else if (status == 'd')
	{	
		if (philo->data->philos_full == philo->data->numberof_philos)
		{
			pthread_mutex_unlock(philo->data->print);
			printf("unlock 3\n");
			return ;
		}
		printf("%d is died\n", philo->id);
	}
	pthread_mutex_unlock(philo->data->print);
	printf("unlock 3\n");
}

void	eating(t_philo *philo)
{
	// pthread_mutex_unlock(philo->data->print);
	pthread_mutex_lock(philo->left_fork);
	pthread_mutex_lock(philo->right_fork);
	print_status(philo, 'l');
	print_status(philo, 'r');
	print_status(philo, 'e');
	pthread_mutex_lock(philo->lock);
	philo->last_meal_time = get_time();
	pthread_mutex_unlock(philo->lock);
	ft_usleep(philo->data->time_to_eat);
	pthread_mutex_lock(philo->lock);
	philo->meals_eaten += 1;
	pthread_mutex_unlock(philo->lock);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	*routine(void *philo_void)
{
	t_philo	*philo;

	philo = (t_philo *)philo_void;
	if (philo->data->numberof_philos == 1)
	{
		case_one(philo);
		return (NULL);
	}
	pthread_mutex_lock(philo->data->check_full);
	pthread_mutex_lock(philo->data->check_death);
	while (philo->data->is_alive
		&& philo->data->philos_full < philo->data->numberof_philos)
	{
		pthread_mutex_unlock(philo->data->check_full);
		pthread_mutex_unlock(philo->data->check_death);
		eating(philo);
		print_status(philo, 's');
		ft_usleep(philo->data->time_to_sleep);
		print_status(philo, 't');
		pthread_mutex_lock(philo->data->check_full);
		pthread_mutex_lock(philo->data->check_death);
	}
	pthread_mutex_unlock(philo->data->check_death);
	pthread_mutex_unlock(philo->data->check_full);
	return (NULL);
}
