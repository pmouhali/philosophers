// 42 Header

#include "philosophers.h"

sem_t *semaphore;

int		main(int ac, char *av[])
{
	int *philosopher_ids;
	pthread_t *thread_ids;

	if (simulation_init(&simulation, ac, av))
		return (EXIT_FAILURE);
	if ((semaphore = sem_open(SEMKEY, O_CREAT, S_IRWXU, simulation.n_philosophers)) == SEM_FAILED)
	{
		simulation_delete(NULL, NULL, NULL);
		return (EXIT_FAILURE);
	}
	philosopher_ids = malloc(sizeof(int*) * simulation.n_philosophers);
	thread_ids = malloc(sizeof(pthread_t*) * simulation.n_philosophers);
	create_threads(thread_ids, philosopher_ids);
	end_checker();
	wait_threads(thread_ids);
	simulation_delete(thread_ids, philosopher_ids, semaphore);
	return (EXIT_SUCCESS);
}
