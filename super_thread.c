/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   super_thread.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbajji <cbajji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 17:26:57 by cbajji            #+#    #+#             */
/*   Updated: 2024/11/09 21:29:05 by cbajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*philo_died(t_philo *philo)
{
	set_check_death(philo, 0);
	pthread_mutex_lock(&philo->data->print);
	printf ("🥀🥀%lld %d died 🥀🥀\n", get_time() - philo->start_time, philo->id);
	pthread_mutex_unlock(&philo->data->print);
	return (NULL);
}

void	all_full(t_philo *philos)
{
	pthread_mutex_lock(&philos->data->print);
	printf ("all philos ate %d meals 🏅\n", philos->data->numberof_meals);
	pthread_mutex_unlock(&philos->data->print);
}

void	one_more_full(t_philo *philos, int i)
{
	set_check_full(philos);
	philos[i].flag = 1;
}

void	*supervisor(void *philos_void)
{
	t_philo	*philos;
	int		i;

	philos = (t_philo *)philos_void;
	while (get_check_full(philos) < philos->data->numberof_philos)
	{
		i = -1;
		while (++i < philos->data->numberof_philos)
		{
			if (get_time() - get_lasttime(&philos[i])
				>= philos->data->time_to_die)
			{
				return (philo_died(philos));
			}
			if (philos->data->numberof_meals != -1 && get_nmeals(&philos[i])
				== philos->data->numberof_meals && !philos[i].flag)
			{
				one_more_full(philos, i);
			}
		}
	}
	all_full(philos);
	return (NULL);
}

void	create_super_thread(t_data *data)
{
	pthread_t	super_thread;

	if (pthread_create(&super_thread, NULL, supervisor,
			(void *)data->philosophers) != 0)
	{
		printf("Error creating supervisor thread\n");
		return ;
	}
	if (pthread_join(super_thread, NULL) != 0)
	{
		printf("Error joining supervisor thread\n");
		return ;
	}
}
