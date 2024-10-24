#include "philosophers.h"

void init_data(t_data *data)
{
	int i;

	i = 0;
	pthread_mutex_init(&data->print, NULL);
	pthread_mutex_init(&data->check_death, NULL);
	pthread_mutex_init(&data->check_full, NULL);
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
		data->philosophers[i].last_meal_time = get_time();
		data->philosophers[i].flag = 0;
		data->philosophers[i].meals_eaten = 0;
		pthread_mutex_init(&data->philosophers[i].lock_lasttime, NULL);
		pthread_mutex_init(&data->philosophers[i].lock_nmeals, NULL);
		i++;
	}
}


void create_threads(t_data *data)
{
	int i;
	
	i = 0;
	while (i < data->numberof_philos)
	{
		data->philosophers[i].start_time = get_time();
		if(pthread_create(&data->philosophers[i].thread, NULL, &routine, (void *)&data->philosophers[i]) != 0)
			return ;
		i++;
	}
	create_super_thread(data);
	i = 0;
	while (i < data->numberof_philos)
	{
		if(pthread_join(data->philosophers[i].thread, NULL) != 0)
			return ;
		i++;
	}
}
void f()
{
	system("leaks philo");
}

int main(int ac, char **av)
{
	// atexit(f);
	t_data data;
	if (!parse(ac, av, &data))
	{
		printf("error in arguments\n");
		return (1);
	}
	data.philos_full = 0;
	data.is_alive = 1;
	init_data(&data);
	create_threads(&data);
	pthread_mutex_destroy(&data.print);
	int i = 0;
	while (i < data.numberof_philos)
	{
		pthread_mutex_destroy(&data.philosophers[i].lock_lasttime);
		pthread_mutex_destroy(&data.philosophers[i].lock_nmeals);
		pthread_mutex_destroy(&data.forks[i]);
		i++;
	}
	c_malloc(0, 0);
}
