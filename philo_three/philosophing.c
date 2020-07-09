// 42 Header

#include "philosophers.h"

void	philosopher_sleep(int n)
{
//	if (simulation.stop == TRUE)
//		return ;
	message(n, SLEEPING);
	usleep(simulation.time_to_sleep * 1000);
}

void	philosopher_think(int n)
{
//	if (simulation.stop == TRUE)
//		return ;
	message(n, THINKING);
}

int		philosopher_eat(int n, struct timeval *last_meal)
{
	sem_wait(forks);					// SEMAPHORE -1 fourchette
//	if (simulation.stop == TRUE)
//		return (FALSE);
	message(n, TAKING_FORK);				// notification
	sem_wait(forks);					// SEMAPHORE -1 fourchette
//	if (simulation.stop == TRUE)
//		return (FALSE);
	message(n, TAKING_FORK);				// notification
//	simulation.meals_per_philosopher[n - 1] += 1;
	message(n, EATING);						// notification
	gettimeofday(last_meal, NULL);			// enregistre l'heure du repas 
//	simulation.philosophers_last_meals[n - 1] = *last_meal;
	usleep(simulation.time_to_eat * 1000);	// mange
	sem_post(forks); 					// SEMAPHORE +1 fourchette
	sem_post(forks); 					// SEMAPHORE +1 fourchette
	return (TRUE);
}

/*
void	end_checker(void)
{
	unsigned int i;
	struct timeval now;
	
	while (simulation.stop == FALSE)
	{
		// Vérifier si un philosophe est mort
		i = -1;
		gettimeofday(&now, NULL);
		while (++i < simulation.n_philosophers)
		{
			if (elapsed_time(simulation.philosophers_last_meals[i], now) > simulation.time_to_die)
			{
				simulation.stop = TRUE;
				message(i + 1, DEAD);
				i = -1;
				while (++i < simulation.n_philosophers)
					sem_post(semaphore); 		// SEMAPHORE +n jeton de débloquage
				return ;
			}
		}
		// Vérifier si tout les repas ont été effectués
		if (simulation.meals_per_philosopher_before_stop > 0)
		{
			i = 0;
			while (simulation.meals_per_philosopher[i] >= simulation.meals_per_philosopher_before_stop)
				i++;
			simulation.stop = i == simulation.n_philosophers ? TRUE : FALSE;
		}
	}
}
*/

void	*philosophing(void *arg)
{
	unsigned int n;

	last_meal = simulation.start;
	n = *(unsigned int*)arg;
	while (TRUE)							// zone critique mais le résultat n'est pas impacté négativement
	{
		philosopher_eat(n, &last_meal);
		philosopher_sleep(n);
		philosopher_think(n);
	}
	return (NULL);
}
