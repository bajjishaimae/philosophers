#ifndef PHILOSOPHERS_H
#define PHILOSOPHERS_H

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>


typedef struct s_philo
{
    int id;
    long long start_time;
    pthread_t thread;
    long long last_meal_time;
    int meals_eaten;
    int flag;
    pthread_mutex_t *right_fork;
    pthread_mutex_t *left_fork;
    pthread_mutex_t *lock;
    struct s_data *data;
} t_philo;

typedef struct s_data
{
    int time_to_eat;
    int time_to_die;
    int time_to_sleep;
    int numberof_philos;
    int numberof_meals;
    int is_alive;
    int philos_full;
    pthread_mutex_t* print;
    pthread_mutex_t* check_death;
    pthread_mutex_t* check_meals;
    pthread_mutex_t* check_full;
    t_philo *philosophers;
    pthread_mutex_t *forks;
} t_data;

typedef struct s_coll{
    void *ptr;
    struct s_coll *next;
} t_coll;

void    *c_malloc(size_t size, int flag);
void *supervisor(void *data_void);
long long get_time();
int parse(int ac, char **av, t_data *data);
void print_status(t_philo *philo, char status);
void create_super_thread(t_data *data);
void	*routine(void *philo_void);
int	ft_usleep(size_t milliseconds);

#endif