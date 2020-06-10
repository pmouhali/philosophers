// 42 Header

#include "philosophers.h"

void	simulation_delete(void *t1, void *t2, sem_t *semaphore)
{
	sem_close(semaphore);
	free(simulation.meals_per_philosopher);
	free(t1);
	free(t2);
}
