// 42 HEADER

#include "philosophers.h"

int		simulation_init(t_simulation_data *sim, int ac, char **av)
{
	if (ac < 5)
	{
		write(1, USAGE, ft_strlen(USAGE));
		return (1);
	}
	sim->n_philosophers = ft_atoi(av[1]);
	if (sim->n_philosophers < 0)
		return (1);
	sim->time_to_die = ft_atoi(av[2]);
	sim->time_to_eat = ft_atoi(av[3]);
	sim->time_to_sleep = ft_atoi(av[4]);
	sim->meals_per_philosopher_before_stop = ac > 5 ? ft_atoi(av[5]) : 0;
	sim->stop = FALSE;
	sim->forks = sim->n_philosophers;
	sim->meals_per_philosopher = malloc(sizeof(char) * (sim->n_philosophers + 1));
	memset(sim->meals_per_philosopher, 0, sizeof(char) * (sim->n_philosophers + 1));
	gettimeofday(&(sim->start), NULL);
	return (0);
}
