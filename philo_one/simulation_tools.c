// 42 HEADER

#include "philosophers.h"

int		simulation_init(t_simulation_data *sim, int ac, char **av)
{
	unsigned int i;

	if (ac < 5 || (sim->n_philosophers = ft_atoi(av[1])) > MAX_PHILOS)
	{
		write(1, USAGE, ft_strlen(USAGE));
		return (1);
	}
	sim->time_to_die = ft_atoi(av[2]);
	sim->time_to_eat = ft_atoi(av[3]);
	sim->time_to_sleep = ft_atoi(av[4]);
	sim->meals_per_philosopher_before_stop = ac > 5 ? ft_atoi(av[5]) : 0;
	sim->stop = FALSE;
	memset(sim->table, 0, sizeof(unsigned char) * MAX_PHILOS);
	memset(sim->table, 1, sizeof(char) * sim->n_philosophers);
	memset(sim->meals_per_philosopher, 0, sizeof(char) * (sim->n_philosophers + 1));
	gettimeofday(&(sim->start), NULL);
	i = -1;
	while (++i < sim->n_philosophers)
		sim->meals_time[i] = sim->start;
	i = -1;
	while (++i < sim->n_philosophers)
		pthread_mutex_init(&(sim->mutexes[i]), NULL);
	return (0);
}

void	simulation_end(t_simulation_data *simulation)
{
	unsigned int i;

	i = -1;
	while (++i < simulation->n_philosophers)
		pthread_mutex_destroy(&(simulation->mutexes[i]));
}
