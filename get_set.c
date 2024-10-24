/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_set.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbajji <cbajji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 17:48:13 by cbajji            #+#    #+#             */
/*   Updated: 2024/10/23 21:18:59 by cbajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int get_check_death(t_philo *philo)
{
    int i;
    pthread_mutex_lock(&philo->data->check_death);
    i = philo->data->is_alive;
    pthread_mutex_unlock(&philo->data->check_death);
    return (i);
}

void set_check_death(t_philo *philo, int value)
{
    pthread_mutex_lock(&philo->data->check_death);
    philo->data->is_alive = value;
    pthread_mutex_unlock(&philo->data->check_death);
}

int get_check_full(t_philo *philo)
{
    int i;
    pthread_mutex_lock(&philo->data->check_full);
    i = philo->data->philos_full;
    pthread_mutex_unlock(&philo->data->check_full);
    return (i);
}

void set_check_full(t_philo *philo)
{
    pthread_mutex_lock(&philo->data->check_full);
    philo->data->philos_full += 1; 
    pthread_mutex_unlock(&philo->data->check_full);
}

long long get_lasttime(t_philo *philo)
{
    long long i;
    pthread_mutex_lock(&philo->lock_lasttime);
    i = philo->last_meal_time;
    pthread_mutex_unlock(&philo->lock_lasttime);
    return (i);
}

void set_lasttime(t_philo *philo)
{
    pthread_mutex_lock(&philo->lock_lasttime);
	philo->last_meal_time = get_time();
	pthread_mutex_unlock(&philo->lock_lasttime);
}

int get_nmeals(t_philo *philo)
{
    int i;
    pthread_mutex_lock(&philo->lock_nmeals);
    i = philo->meals_eaten;
    pthread_mutex_unlock(&philo->lock_nmeals);
    return (i);
}

void set_nmeals(t_philo *philo)
{
    pthread_mutex_lock(&philo->lock_nmeals);
	philo->meals_eaten += 1;
	pthread_mutex_unlock(&philo->lock_nmeals);
}