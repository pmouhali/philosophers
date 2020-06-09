// 42 Header

#include "philosophers.h"

void	simulation_delete(void *t1, void *t2, pthread_mutex_t *mutex)
{
	free(simulation.meals_per_philosopher);
	free(t1);
	free(t2);
	pthread_mutex_destroy(mutex);
}
