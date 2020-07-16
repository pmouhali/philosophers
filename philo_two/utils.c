// 42 HEADER

#include "philosophers.h"

static void	clear_semaphores()
{
	sem_unlink(SEMFORKS);
	sem_close(forks);
	sem_unlink(SEMEAT);
	sem_close(eat);
}

int		simulation_init(t_simulation_data *sim, int ac, char **av)
{
	unsigned int i;
	
	clear_semaphores();
	if (ac < 5 || (sim->n = ft_atoi(av[1])) > MAX_PHILOS)
	{
		write(1, USAGE, ft_strlen(USAGE));
		return (1);
	}
	sim->time_to_die = ft_atoi(av[2]);
	sim->time_to_eat = ft_atoi(av[3]);
	sim->time_to_sleep = ft_atoi(av[4]);
	sim->meals_option = ac > 5 ? ft_atoi(av[5]) : 0;
	sim->stop = FALSE;
	sim->meals_count = malloc(sizeof(char) * (sim->n + 1));
	memset(sim->meals_count, 0, sizeof(char) * (sim->n + 1));
	gettimeofday(&(sim->start), NULL);
	sim->meals_time = malloc(sizeof(*(sim->meals_time)) * (sim->n + 1));
	i = 0;
	while (i < sim->n)
	{
		sim->meals_time[i] = sim->start;
		i++;
	}
	return (0);
}

void	simulation_delete(void *t1, void *t2)
{
	clear_semaphores();
	free(simulation.meals_count);
	free(simulation.meals_time);
	free(t1);
	free(t2);
}

void	create_threads(pthread_t *thread_ids, int *philosopher_ids)
{
	unsigned int i;

	i = 0;
	while (i < simulation.n)
	{
		philosopher_ids[i] = i;
		pthread_create(&thread_ids[i], NULL, philosophing, &philosopher_ids[i]);
		i++;
	}
}

void	wait_threads(pthread_t *thread_ids)
{
	unsigned int i;

	i = 0;
	while (i < simulation.n)
	{
		pthread_join(thread_ids[i], NULL);
		i++;
	}
}
