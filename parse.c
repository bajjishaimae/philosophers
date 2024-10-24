#include "philosophers.h"

int contains_digitsonly(char *av)
{
    int i;
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

int parse(int ac, char **av, t_data *data)
{
    int i;

    i = 1;
    if (ac == 5 || ac == 6)
	{
		while (av[i])
        {
            if (!contains_digitsonly(av[i]))
                return (0);
            i++;
        }
        data->numberof_philos = atoi(av[1]);
	    data->time_to_die = atoi(av[2]);
	    data->time_to_eat = atoi(av[3]);
	    data->time_to_sleep = atoi(av[4]);
	    if (ac == 6)
		    data->numberof_meals = atoi(av[5]);
        if(!data->numberof_philos || data->numberof_philos > 200 || !data->time_to_die || !data->time_to_eat || !data->time_to_sleep || !data->numberof_meals)
        {
            return (0);
        }
        if (!av[5])
            data->numberof_meals = -1;
        return (1);
	}
    return (0);
}
