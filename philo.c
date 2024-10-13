#include "philosophers.h"

void init_data(t_data *data)
{
	int i;

	i = 0;
	data->forks = c_malloc(sizeof(pthread_mutex_t) * data->numberof_philos, 1);
	while (i < data->numberof_philos)
	{
		pthread_mutex_init(&data->forks[i], NULL);
		i++;
	}
	i = 0;
	data->philosophers = c_malloc(sizeof(t_philo) * data->numberof_philos, 1);
	while (i < data->numberof_philos)
	{
		data->philosophers[i].id = i + 1;
		data->philosophers[i].left_fork = &data->forks[i];
		data->philosophers[i].right_fork = &data->forks[(i + 1) % data->numberof_philos];
		data->philosophers[i].data = data;
		data->philosophers[i].lock = c_malloc(sizeof(pthread_mutex_t), 1);
		pthread_mutex_init(data->philosophers[i].lock, NULL);
		i++;
	}
}

long long get_time()
{
	struct timeval time;
	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000)); //1s = 1000 ms, 1ms = 1000us
}

/*
eat
sleep
think
*/
void *routine(void *arg)
{
    t_philo *philo = (t_philo *)arg;
    
    while (1)
    {
        // Check if simulation is still running
        pthread_mutex_lock(philo->data->alive);
        if (!philo->data->is_alive) // If a philosopher is dead, stop
        {
            pthread_mutex_unlock(philo->data->alive);
            break;
        }
        pthread_mutex_unlock(philo->data->alive);

        // Try to pick up forks based on philosopher's ID
        if (philo->id % 2 == 0)
        {
            pthread_mutex_lock(philo->right_fork);
            pthread_mutex_lock(philo->left_fork);
        }
        else
        {
            pthread_mutex_lock(philo->left_fork);
            pthread_mutex_lock(philo->right_fork);
        }

        // Eating
        pthread_mutex_lock(philo->data->print);
		// if (philo->data->is_alive){
		pthread_mutex_lock(philo->data->alive);
        if (!philo->data->is_alive) // If a philosopher is dead, stop
        {
            pthread_mutex_unlock(philo->data->alive);
			pthread_mutex_unlock(philo->data->print);
			pthread_mutex_unlock(philo->left_fork);
        	pthread_mutex_unlock(philo->right_fork);
            break;
        }
		else {
        	pthread_mutex_unlock(philo->data->alive);
        	printf("%d has taken a fork\n", philo->id);
        	printf("%d is eating\n", philo->id);
		}
        pthread_mutex_unlock(philo->data->print);

        philo->last_meal_time = get_time();
        usleep(philo->data->time_to_eat * 1000); // Simulate eating time

        pthread_mutex_unlock(philo->left_fork);
        pthread_mutex_unlock(philo->right_fork);

        // Sleeping
        pthread_mutex_lock(philo->data->print);
		if (!philo->data->is_alive) // If a philosopher is dead, stop
        {
            pthread_mutex_unlock(philo->data->alive);
			pthread_mutex_unlock(philo->data->print);
            break;
        }
		else {
			pthread_mutex_unlock(philo->data->alive);
        	printf("%d is sleeping\n", philo->id);
		}
        pthread_mutex_unlock(philo->data->print);
        usleep(philo->data->time_to_sleep * 1000); // Simulate sleeping time

        // Check if philosopher has died
        pthread_mutex_lock(philo->data->alive);
		if (!philo->data->is_alive) break ;
        if (get_time() - philo->last_meal_time > philo->data->time_to_die)
        {
            pthread_mutex_lock(philo->data->print);
            printf("%d has died\n", philo->id);
            pthread_mutex_unlock(philo->data->print);

            philo->data->is_alive = 0; // Signal that a philosopher has died
            pthread_mutex_unlock(philo->data->alive);
            break; // Exit the routine if the philosopher dies
        }
        pthread_mutex_unlock(philo->data->alive);

        // Thinking
        pthread_mutex_lock(philo->data->print);
		if (!philo->data->is_alive) // If a philosopher is dead, stop
        {
            pthread_mutex_unlock(philo->data->alive);
			pthread_mutex_unlock(philo->data->print);
            break;
        }
		else {
			pthread_mutex_unlock(philo->data->alive);
        	printf("%d is thinking\n", philo->id);
		}
        pthread_mutex_unlock(philo->data->print);
    }
    return arg;
}
// void create_threads(t_philo *philo)
// {
// 	int i = 0;
// 	while (i < philo->data->numberof_philos)
// 	{
// 		if (pthread_create(&philo[i].thread, NULL, &routine, (void *)))
// 	}
// }



int main(int ac, char **av)
{
	(void)ac;
	t_data data;
	int i = 0;
	data.print = c_malloc(sizeof(pthread_mutex_t), 1);
	pthread_mutex_init(data.print, NULL);
	data.alive = c_malloc (sizeof(pthread_mutex_t), 1);
	pthread_mutex_init(data.alive, NULL);
	data.numberof_philos = atoi(av[1]);
	data.time_to_die = atoi(av[2]);
	data.time_to_eat = atoi(av[3]);
	data.time_to_sleep = atoi(av[4]);
	if (av[5])
		data.numberof_meals = atoi(av[5]);
	data.is_alive = 1;
	init_data(&data);
	while (i < data.numberof_philos)
	{
		if (data.philosophers[i].id % 2 == 0)
			pthread_create(&data.philosophers[i].thread, NULL, routine, &data.philosophers[i]);
		i++;
	}
	i = 0;
	while (i < data.numberof_philos)
	{
		if (data.philosophers[i].id % 2 != 0)
			pthread_create(&data.philosophers[i].thread, NULL, routine, &data.philosophers[i]);
		i++;
	}
	i = 0;
	while (i < data.numberof_philos)
	{
		pthread_join(data.philosophers[i].thread, NULL);
		i++;
	}

	// pthread_t supervisor_thread;

	// if (pthread_create(&supervisor_thread, NULL, &supervisor, (void *)&data) != 0)
	// {
    // 	printf("Error creating supervisor thread\n");
    // 	return 1;
	// }

// // Join the supervisor thread to wait for it to finish
// 	if (pthread_join(supervisor_thread, NULL) != 0)
// 	{
//     	printf("Error joining supervisor thread\n");
//     	return 1;
// 	}

}
