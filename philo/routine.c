/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbajji <cbajji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 11:18:36 by cbajji            #+#    #+#             */
/*   Updated: 2024/11/22 17:00:04 by cbajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	create_threads(t_data *data)
{
	int	i;

	i = 0;
	data->start_time = get_time();
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

void	eating_and_sleeping(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	print_status1(philo, 'l');
	pthread_mutex_lock(philo->right_fork);
	print_status1(philo, 'r');
	print_status2(philo, 'e');
	set_lasttime(philo);
	ft_usleep(philo->data->time_to_eat, philo);
	set_nmeals(philo);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	if (!get_check_death(philo))
		return ;
	print_status2(philo, 's');
	ft_usleep(philo->data->time_to_sleep, philo);
}

void	*routine(void *philo_void)
{
	t_philo	*philo;

	philo = (t_philo *)philo_void;
	if (philo->data->numberof_philos == 1)
	{
		print_status1(philo, 'l');
		return (NULL);
	}
	if (philo->id % 2 == 0)
		ft_usleep(philo->data->time_to_eat, philo);
	while (1)
	{
		eating_and_sleeping(philo);
		if (!get_check_death(philo) || (philo->data->numberof_meals != -1
				&& get_nmeals(philo) == philo->data->numberof_meals))
			break ;
		print_status2(philo, 't');
		if (!get_check_death(philo) || (philo->data->numberof_meals != -1
				&& get_nmeals(philo) == philo->data->numberof_meals))
			break ;
	}
	return (NULL);
}
