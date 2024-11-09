/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_set2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbajji <cbajji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 17:53:40 by cbajji            #+#    #+#             */
/*   Updated: 2024/11/09 18:03:38 by cbajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long long	get_lasttime(t_philo *philo)
{
	long long	i;

	pthread_mutex_lock(&philo->lock_lasttime);
	i = philo->last_meal_time;
	pthread_mutex_unlock(&philo->lock_lasttime);
	return (i);
}

void	set_lasttime(t_philo *philo)
{
	pthread_mutex_lock(&philo->lock_lasttime);
	philo->last_meal_time = get_time();
	pthread_mutex_unlock(&philo->lock_lasttime);
}

int	get_nmeals(t_philo *philo)
{
	int	i;

	pthread_mutex_lock(&philo->lock_nmeals);
	i = philo->meals_eaten;
	pthread_mutex_unlock(&philo->lock_nmeals);
	return (i);
}

void	set_nmeals(t_philo *philo)
{
	pthread_mutex_lock(&philo->lock_nmeals);
	philo->meals_eaten += 1;
	pthread_mutex_unlock(&philo->lock_nmeals);
}
