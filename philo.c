#include "philosophers.h"

void init_data(t_data *data)
{
	int i;

	i = 0;
	data->print = c_malloc(sizeof(pthread_mutex_t), 1);
	pthread_mutex_init(data->print, NULL);
	data->alive = c_malloc (sizeof(pthread_mutex_t), 1);
	pthread_mutex_init(data->alive, NULL);
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
		if (data->philosophers->id % 2 == 0)
		{
			data->philosophers[i].right_fork = &data->forks[i];
			data->philosophers[i].left_fork = &data->forks[(i + 1) % data->numberof_philos];
		}
		else
		{
			data->philosophers[i].left_fork = &data->forks[i];
			data->philosophers[i].right_fork = &data->forks[(i + 1) % data->numberof_philos];
		}
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
int	ft_usleep(size_t milliseconds)
{
	size_t	start;

	start = get_time();
	while ((get_time() - start) < milliseconds)
		usleep(500);
	return (0);
}

void print_status(t_philo *philo, char status)
{

	pthread_mutex_lock(philo->data->print);
	if (status == 'r')
		printf("%d takes the right fork\n", philo->id);
	else if (status == 'l')
		printf("%d takes the left fork\n", philo->id);
	else if (status == 'e')
		printf("%d is eating\n", philo->id);
	else if (status == 's')
		printf("%d is sleeping\n", philo->id);
	else if (status == 't')
		printf("%d is thinking\n", philo->id);
	else if (status == 'd')
		printf("%d is died\n", philo->id);
	pthread_mutex_unlock(philo->data->print);
}

void *routine(void *arg)
{
    t_philo *philo = (t_philo *)arg;
    
    while (1)
    {
        pthread_mutex_lock(philo->data->alive);
        if (!philo->data->is_alive)
        {
            pthread_mutex_unlock(philo->data->alive);
            break;
        }
        pthread_mutex_unlock(philo->data->alive);

            pthread_mutex_lock(philo->left_fork);
			print_status(philo, 'l');
            pthread_mutex_lock(philo->right_fork);
			print_status(philo, 'r');
		pthread_mutex_lock(philo->data->alive);
        if (!philo->data->is_alive) 
        {
            pthread_mutex_unlock(philo->data->alive);
			pthread_mutex_unlock(philo->left_fork);
        	pthread_mutex_unlock(philo->right_fork);
            break;
        }
		else {
        	pthread_mutex_unlock(philo->data->alive);
        	print_status(philo, 'e');
		}

        philo->last_meal_time = get_time();
        ft_usleep(philo->data->time_to_eat);

        pthread_mutex_unlock(philo->left_fork);
        pthread_mutex_unlock(philo->right_fork);

		pthread_mutex_lock(philo->data->alive);
		if (!philo->data->is_alive)
        {
            pthread_mutex_unlock(philo->data->alive);
            break;
        }
		else {
			pthread_mutex_unlock(philo->data->alive);
        	print_status(philo, 's');
		}
        ft_usleep(philo->data->time_to_sleep);

        pthread_mutex_lock(philo->data->alive);
        if (get_time() - philo->last_meal_time > philo->data->time_to_die)
        {
            print_status(philo, 'd');

            philo->data->is_alive = 0;
            pthread_mutex_unlock(philo->data->alive);
            break; 
        }
        pthread_mutex_unlock(philo->data->alive);

		pthread_mutex_lock(philo->data->alive);
		if (!philo->data->is_alive)
        {
            pthread_mutex_unlock(philo->data->alive);
            break;
        }
		else {
			pthread_mutex_unlock(philo->data->alive);
        	print_status(philo, 't');
		}
    }
    return NULL;
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
		usleep(100);
		i++;
	}
	i = 0;
	while (i < data->numberof_philos)
	{
		if(pthread_join(data->philosophers[i].thread, NULL) != 0)
			return ;
		i++;
	}
}


int main(int ac, char **av)
{
	
	t_data data;
	if (!parse(ac, av, &data))
	{
		printf("error in arguments\n");
		return (1);
	}
	data.is_alive = 1;
	init_data(&data);
	create_threads(&data);
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
