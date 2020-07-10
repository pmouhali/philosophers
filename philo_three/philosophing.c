// 42 Header

#include "philosophers.h"

void	philosopher_sleep(int n)
{
	message(n, SLEEPING);
	usleep(simulation.time_to_sleep * 1000);
}

void	philosopher_think(int n)
{
	message(n, THINKING);
}

int		philosopher_eat(int n, struct timeval *last_meal)
{
	sem_wait(forks);					// SEMAPHORE -1 fourchette
	message(n, TAKING_FORK);				// notification
	sem_wait(forks);					// SEMAPHORE -1 fourchette
	message(n, TAKING_FORK);				// notification
	message(n, EATING);						// notification
	n_meals++;
	if (simulation.meals_per_philosopher_before_stop > 0 && n_meals == simulation.meals_per_philosopher_before_stop)
		sem_post(meals);
	gettimeofday(last_meal, NULL);			// enregistre l'heure du repas 
	usleep(simulation.time_to_eat * 1000);	// mange
	sem_post(forks); 					// SEMAPHORE +1 fourchette
	sem_post(forks); 					// SEMAPHORE +1 fourchette
	return (TRUE);
}

void	*philosophing(void *arg)
{
	unsigned int n;

	n = *(unsigned int*)arg;
	while (TRUE)
	{
		philosopher_eat(n, &last_meal);
		philosopher_sleep(n);
		philosopher_think(n);
	}
	return (NULL);
}
