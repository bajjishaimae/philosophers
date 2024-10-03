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
    long long last_meal_time;
    int meals_eaten;
    pthread_mutex_t *right_fork;
    pthread_mutex_t *left_fork;
    struct s_data *data;
} t_philo;

typedef struct s_data
{
    int time_to_eat;
    int time_to_die;
    int time_to_sleep;
    int numberof_philos;
    int numberof_meals;
    int alive;
    pthread_mutex_t print;
    t_philo *philosophers;
    pthread_mutex_t *forks;
} t_data;

typedef struct s_coll{
    void *ptr;
    struct s_coll *next;
} t_coll;

#endif