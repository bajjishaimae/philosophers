/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbajji <cbajji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 11:18:36 by cbajji            #+#    #+#             */
/*   Updated: 2024/10/24 12:23:08 by cbajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void print_status(t_philo *philo, char status)
{
	if (!get_check_death(philo) || get_check_full(philo) == philo->data->numberof_philos)
		return ;
	pthread_mutex_lock(&philo->data->print);
	
	if (status == 'r')
		printf("%lld %d  has taken a fork 🍴\n",get_time() - philo->start_time ,philo->id);
	else if (status == 'l')
		printf("%lld %d  has taken a fork 🍴\n", get_time() - philo->start_time ,philo->id);
	else if (status == 'e')
		printf("%lld %d is eating 🍝\n",get_time() - philo->start_time , philo->id);
	else if (status == 's')
		printf("%lld %d is sleeping 😴\n",get_time() - philo->start_time , philo->id);
	else if (status == 't')
		printf("%lld %d is thinking 💭\n", get_time() - philo->start_time ,philo->id);
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
	ft_usleep(philo->data->time_to_eat);
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
	while (get_check_death(philo) && get_check_full(philo) <= philo->data->numberof_philos)
	{
		eating(philo);
		print_status(philo, 's');
		ft_usleep(philo->data->time_to_sleep);
		print_status(philo, 't');
		if (philo->data->numberof_meals != -1 && get_nmeals(philo) == philo->data->numberof_meals)
		{
			break ;
		}
	}
	return (NULL);
}
