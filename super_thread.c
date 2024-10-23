/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   super_thread.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbajji <cbajji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 17:26:57 by cbajji            #+#    #+#             */
/*   Updated: 2024/10/21 18:37:57 by cbajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void *philo_died(t_philo *philo)
{
    pthread_mutex_lock(philo->data->check_death);
    philo->data->is_alive = 0;
    pthread_mutex_unlock(philo->data->check_death);
    print_status(philo, 'd');
    pthread_mutex_unlock(philo->lock);
    return(NULL);
}

void	all_full(t_philo *philos)
{
	size_t		time;

	time = get_time() - philos->start_time;
	pthread_mutex_lock(philos->data->print);
	printf("all philos ate %d meals\n",philos->data->numberof_meals);
	pthread_mutex_unlock(philos->data->print);
}

void	one_more_full(t_philo *philos, int i)
{
	pthread_mutex_lock(philos->data->check_full);
	philos->data->philos_full += 1;
	pthread_mutex_lock(philos->data->check_full);
	philos[i].flag = 1;
}

void	*supervisor(void *philos_void)
{
	t_philo	*philos;
	int			i;

	philos = (t_philo *)philos_void;
	while (philos->data->philos_full < philos->data->numberof_philos)
	{
		i = -1;
		while (++i < philos->data->numberof_philos)
		{
			pthread_mutex_lock(philos[i].lock);
			if (get_time() - philos[i].last_meal_time >= philos->data->time_to_die)
				return (philo_died(philos));
			pthread_mutex_unlock(philos[i].lock);
			pthread_mutex_lock(philos->lock);
			if (philos[i].meals_eaten == philos->data->numberof_meals && !philos[i].flag)
				one_more_full(philos, i);
			pthread_mutex_unlock(philos->lock);
		}
	}
	all_full(philos);
	return (NULL);
}

void create_super_thread(t_data *data)
{
    pthread_t super_thread;
if (pthread_create(&super_thread, NULL, &supervisor, (void *)data->philosophers) != 0)
{
    printf("Error creating supervisor thread\n");
    return;
}

if (pthread_join(super_thread, NULL) != 0)
{
    printf("Error joining supervisor thread\n");
    return;
}
}

