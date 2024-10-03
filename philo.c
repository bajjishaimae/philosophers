#include "philosophers.h"

void init_data(t_data *data, char **av)
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
		i++;
	}
}

/*
eat
sleep
think
*/
void routine(void *arg)
{
	t_philo *philo = arg;
	while(philo->data->alive)
	{
		pthread_mutex_lock(&philo->left_fork);
		pthread_mutex_lock(&philo->right_fork);

		pthread_mutex_lock(&philo->data->print);
		printf("%d has taken a fork\n", philo->id);
		printf("%d is eating\n", philo->id);
		pthread_mutex_unlock(&philo->data->print);
	
		usleep(philo->data->time_to_eat * 1000);

		pthread_mutex_unlock(&philo->left_fork);
		pthread_mutex_unlock(&philo->right_fork);

		pthread_mutex_lock(&philo->data->print);
		printf("%d is sleeping\n", philo->id);
		pthread_mutex_unlock(&philo->data->print);

		usleep(philo->data->time_to_sleep * 1000);

		pthread_mutex_lock(&philo->data->print);
		printf("%d is thinking\n", philo->id);
		pthread_mutex_unlock(&philo->data->print);
	}
}


int main(int ac, char **av)
{
	t_data data;
	int i = 0;
	pthread_mutex_init(&data.print, NULL);
	data.numberof_philos = atoi(av[1]);
	data.time_to_die = atoi(av[2]);
	data.time_to_eat = atoi(av[3]);
	data.time_to_sleep = atoi(av[4]);
	if (av[5])
		data.numberof_meals = atoi(av[5]);
	while (i < data.numberof_philos)
	{
		pthread_create(&data.philosophers[i], NULL, routine, NULL);
		i++;
	}

	
}