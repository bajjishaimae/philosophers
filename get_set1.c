/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_set1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbajji <cbajji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 17:48:13 by cbajji            #+#    #+#             */
/*   Updated: 2024/11/09 17:54:15 by cbajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	get_check_death(t_philo *philo)
{
	int	i;

	pthread_mutex_lock(&philo->data->check_death);
	i = philo->data->is_alive;
	pthread_mutex_unlock(&philo->data->check_death);
	return (i);
}

void	set_check_death(t_philo *philo, int value)
{
	pthread_mutex_lock(&philo->data->check_death);
	philo->data->is_alive = value;
	pthread_mutex_unlock(&philo->data->check_death);
}

int	get_check_full(t_philo *philo)
{
	int	i;

	pthread_mutex_lock(&philo->data->check_full);
	i = philo->data->philos_full;
	pthread_mutex_unlock(&philo->data->check_full);
	return (i);
}

void	set_check_full(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->check_full);
	philo->data->philos_full += 1;
	pthread_mutex_unlock(&philo->data->check_full);
}
