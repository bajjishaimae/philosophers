/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbajji <cbajji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 21:37:51 by cbajji            #+#    #+#             */
/*   Updated: 2024/11/10 19:11:31 by cbajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	contains_digitsonly(char *av)
{
	int	i;

	i = 0;
	while (av[i])
	{
		if (av[i] >= '0' && av[i] <= '9')
			i++;
		else
			return (0);
	}
	return (1);
}

int	parse(int ac, char **av, t_data *data, int i)
{
	if (ac == 5 || ac == 6)
	{
		while (av[i])
		{
			if (!contains_digitsonly(av[i]))
				return (0);
			i++;
		}
		data->numberof_philos = ft_atoi(av[1]);
		data->time_to_die = ft_atoi(av[2]);
		data->time_to_eat = ft_atoi(av[3]);
		data->time_to_sleep = ft_atoi(av[4]);
		if (ac == 6)
			data->numberof_meals = ft_atoi(av[5]);
		else
			data->numberof_meals = -1;
		if (!data->numberof_philos || !data->numberof_meals)
			return (0);
		return (1);
	}
	return (0);
}
