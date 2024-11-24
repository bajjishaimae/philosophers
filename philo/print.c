/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbajji <cbajji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 15:03:35 by cbajji            #+#    #+#             */
/*   Updated: 2024/11/22 15:27:48 by cbajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check_death_for_print(t_philo *philo)
{
	if (!get_check_death(philo))
	{
		pthread_mutex_unlock(&philo->data->print);
		return (1);
	}
	return (0);
}

void	print_status1(t_philo *philo, char status)
{
	if (check_death_for_print(philo))
		return ;
	pthread_mutex_lock(&philo->data->print);
	if (check_death_for_print(philo))
		return ;
	if (status == 'r')
	{
		printf ("%lld %d has taken a fork\n", get_time()
			- philo->data->start_time, philo->id);
		if (check_death_for_print(philo))
			return ;
	}
	else if (status == 'l')
	{
		printf ("%lld %d has taken a fork\n", get_time()
			- philo->data->start_time, philo->id);
		if (check_death_for_print(philo))
			return ;
	}
	pthread_mutex_unlock(&philo->data->print);
}

void	print_status2(t_philo *philo, char status)
{
	if (check_death_for_print(philo))
		return ;
	pthread_mutex_lock(&philo->data->print);
	if (check_death_for_print(philo))
		return ;
	else if (status == 'e')
	{
		printf ("%lld %d is eating\n", get_time()
			- philo->data->start_time, philo->id);
		if (check_death_for_print(philo))
			return ;
	}
	else if (status == 's')
	{
		printf ("%lld %d is sleeping\n", get_time()
			- philo->data->start_time, philo->id);
		if (check_death_for_print(philo))
			return ;
	}
	else if (status == 't')
	{
		printf ("%lld %d is thinking\n", get_time()
			- philo->data->start_time, philo->id);
	}
	pthread_mutex_unlock(&philo->data->print);
}
