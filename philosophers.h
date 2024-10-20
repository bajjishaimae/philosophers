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
    pthread_mutex_t *alive;
    int is_alive;
    pthread_mutex_t* print;
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

#endif