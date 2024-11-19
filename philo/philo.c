/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbajji <cbajji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 21:41:20 by cbajji            #+#    #+#             */
/*   Updated: 2024/11/18 18:32:32 by cbajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	init_forks(t_data *data, t_cleanup_state *state)
{
	int	i;

	i = 0;
	while (i < data->numberof_philos)
	{
		if (pthread_mutex_init(&data->forks[i], NULL))
		{
			state->forks_initialized = i;
			return (0);
		}
		i++;
	}
	state->forks_initialized = data->numberof_philos;
	return (1);
}

int	init_philo_mutex(t_data *data, t_cleanup_state *state)
{
	int	i;

	i = 0;
	while (i < data->numberof_philos)
	{
		if (pthread_mutex_init(&data->philosophers[i].lock_lasttime, NULL))
		{
			state->philos_initialized = i;
			return (0);
		}
		if (pthread_mutex_init(&data->philosophers[i].lock_nmeals, NULL))
		{
			safe_mutex_destroy(&data->philosophers[i].lock_lasttime,
				"lock_lasttime");
			state->philos_initialized = i;
			return (0);
		}
		i++;
	}
	state->philos_initialized = data->numberof_philos;
	return (1);
}

int	init_data_mutex(t_data *data, t_cleanup_state *state)
{
	if (pthread_mutex_init(&data->print, NULL))
		return (0);
	if (pthread_mutex_init(&data->check_death, NULL))
	{
		safe_mutex_destroy(&data->print, "print");
		return (0);
	}
	if (pthread_mutex_init(&data->check_full, NULL))
	{
		safe_mutex_destroy(&data->print, "print");
		safe_mutex_destroy(&data->check_death, "check death");
		return (0);
	}
	state->data_mutex_initialized = 1;
	return (1);
}

int	init_data(t_data *data, int i)
{
	data->forks = malloc(sizeof(pthread_mutex_t) * data->numberof_philos);
	if (!data->forks)
		return (0);
	data->philosophers = malloc(sizeof(t_philo) * data->numberof_philos);
	if (!data->philosophers)
	{
		free(data->forks);
		return (0);
	}
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
	return (1);
}

int	main(int ac, char **av)
{
	t_data			data;
	t_cleanup_state	state;

	if (!parse(ac, av, &data, 1))
	{
		printf("error in arguments\n");
		return (1);
	}
	data.philos_full = 0;
	data.is_alive = 1;
	if (!init_data(&data, 0))
	{
		printf ("allocation failed\n");
		return (1);
	}
	if (!init_forks(&data, &state)
		|| !init_philo_mutex(&data, &state)
		|| !init_data_mutex(&data, &state))
	{
		cleanup(&data, &state);
		printf ("Initialization failed\n");
		return (1);
	}
	create_threads(&data);
	cleanup(&data, &state);
}
