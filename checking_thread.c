/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checking_thread.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbajji <cbajji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 14:57:10 by cbajji            #+#    #+#             */
/*   Updated: 2024/10/06 14:25:27 by cbajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "philosophers.h"



void *supervisor(void *data_void)
{
    t_data *data = (t_data *)data_void;
    int i;

    while (data->is_alive) // Monitor until a philosopher dies
    {
        i = 0;
        while (i < data->numberof_philos)
        {
            pthread_mutex_lock(data->philosophers[i].lock);
            // Check if the philosopher has died
            if (get_time() - data->philosophers[i].last_meal_time > data->time_to_die)
            {
                data->is_alive = 0; // Stop the simulation
                pthread_mutex_lock(data->print);
                printf("%d died\n", data->philosophers[i].id);
                pthread_mutex_unlock(data->print);
                pthread_mutex_unlock(data->philosophers[i].lock);
                return NULL;
            }
            pthread_mutex_unlock(data->philosophers[i].lock);

            // Optional: Check if all philosophers have eaten enough meals
            // ...
            i++;
        } // Sleep a little to avoid busy waiting
    }
    return NULL;
}
