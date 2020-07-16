// 42 Header

#include "philosophers.h"

sem_t *forks;
sem_t *eat;

int		main(int ac, char *av[])
{
	int *philosopher_ids;
	pthread_t *thread_ids;

	if (simulation_init(&simulation, ac, av))
		return (EXIT_FAILURE);
	if ((forks = sem_open(SEMFORKS, O_CREAT, S_IRWXU, simulation.n)) == SEM_FAILED
		|| (eat = sem_open(SEMEAT, O_CREAT, S_IRWXU, simulation.n)) == SEM_FAILED
	)
	{
		simulation_delete(NULL, NULL);
		return (EXIT_FAILURE);
	}
	philosopher_ids = malloc(sizeof(int*) * simulation.n);
	thread_ids = malloc(sizeof(pthread_t*) * simulation.n);
	create_threads(thread_ids, philosopher_ids);
	end_checker();
	wait_threads(thread_ids);
	simulation_delete(thread_ids, philosopher_ids);
	return (EXIT_SUCCESS);
}
