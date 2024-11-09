/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbajji <cbajji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 21:41:20 by cbajji            #+#    #+#             */
/*   Updated: 2024/11/09 21:48:19 by cbajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	free_and_destroy(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->numberof_philos)
	{
		pthread_mutex_destroy(&data->philosophers[i].lock_lasttime);
		pthread_mutex_destroy(&data->philosophers[i].lock_nmeals);
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	free(data->forks);
	free(data->philosophers);
	pthread_mutex_destroy(&data->check_death);
	pthread_mutex_destroy(&data->check_full);
	pthread_mutex_destroy(&data->print);
}

int	init_mutex(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->numberof_philos)
	{
		if (pthread_mutex_init(&data->forks[i], NULL))
			return (0);
		if (pthread_mutex_init(&data->philosophers[i].lock_lasttime, NULL)
			|| pthread_mutex_init(&data->philosophers[i].lock_nmeals, NULL))
			return (0);
		i++;
	}
	if (pthread_mutex_init(&data->print, NULL)
		|| pthread_mutex_init(&data->check_death, NULL)
		|| pthread_mutex_init(&data->check_full, NULL))
		return (0);
	return (1);
}

void	init_data(t_data *data, int i)
{
	data->forks = malloc(sizeof(pthread_mutex_t) * data->numberof_philos);
	if (!data->forks)
		return ;
	data->philosophers = malloc(sizeof(t_philo) * data->numberof_philos);
	if (!data->philosophers)
		return ;
	while (i < data->numberof_philos)
	{
		data->philosophers[i].id = i + 1;
		data->philosophers[i].left_fork = &data->forks[i];
		data->philosophers[i].right_fork = &data->forks[(i + 1)
			% data->numberof_philos];
		data->philosophers[i].data = data;
		data->philosophers[i].last_meal_time = get_time();
		data->philosophers[i].flag = 0;
		data->philosophers[i].meals_eaten = 0;
		i++;
	}
}

void	create_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->numberof_philos)
	{
		data->philosophers[i].start_time = get_time();
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

int	main(int ac, char **av)
{
	t_data	data;

	if (!parse(ac, av, &data, 1))
	{
		printf("error in arguments\n");
		return (1);
	}
	data.philos_full = 0;
	data.is_alive = 1;
	init_data(&data, 0);
	if (!init_mutex(&data))
	{
		printf("Error in init mutex\n");
		return (1);
	}
	create_threads(&data);
	free_and_destroy(&data);
}
