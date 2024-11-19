/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbajji <cbajji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 17:38:10 by cbajji            #+#    #+#             */
/*   Updated: 2024/11/18 18:33:00 by cbajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

void	safe_mutex_destroy(pthread_mutex_t *mutex, char *name)
{
	if (pthread_mutex_destroy(mutex) != 0)
	{
		write(2, "Failed to destroy mutex: ", 25);
		write(2, name, ft_strlen(name));
	}
}

void	cleanup(t_data *data, t_cleanup_state *state)
{
	int	i;

	i = 0;
	while (i < state->philos_initialized)
	{
		safe_mutex_destroy(&data->philosophers[i].lock_lasttime,
			"lock_lasttime");
		safe_mutex_destroy(&data->philosophers[i].lock_nmeals, "lock_nmeals");
		i++;
	}
	i = 0;
	while (i < state->forks_initialized)
	{
		safe_mutex_destroy(&data->forks[i], "fork");
		i++;
	}
	if (state->data_mutex_initialized)
	{
		safe_mutex_destroy(&data->print, "print");
		safe_mutex_destroy(&data->check_death, "check_death");
		safe_mutex_destroy(&data->check_full, "check_full");
	}
	free(data->philosophers);
	free(data->forks);
}
