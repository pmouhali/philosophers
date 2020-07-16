// 42 Header

#include "philosophers.h"

void	end_checker(void)
{
	unsigned int i;
	struct timeval now;
	
	while (simulation.stop == FALSE)
	{
		// Vérifier si un philosophe est mort
		i = -1;
		while (++i < simulation.n)
		{
			sem_wait(eat);
			gettimeofday(&now, NULL);
			sem_post(eat);
			if (elapsed_time(simulation.meals_time[i], now) > simulation.time_to_die)
			{
				simulation.stop = TRUE;
				message(i + 1, DEAD);
				i = -1;
				while (++i < simulation.n)
					sem_post(forks); 		// SEMAPHORE +n jeton de débloquage
				return ;
			}
		}
		// Vérifier si tout les repas ont été effectués
		if (simulation.meals_option > 0)
		{
			i = 0;
			while (simulation.meals_count[i] >= simulation.meals_option)
				i++;
			simulation.stop = i == simulation.n ? TRUE : FALSE;
		}
	}
}

/*
void	philosopher_sleep(int n)
{
	if (simulation.stop == TRUE)
		return ;
	message(n, SLEEPING);
	usleep(simulation.time_to_sleep * 1000);
}

void	philosopher_think(int n)
{
	if (simulation.stop == TRUE)
		return ;
	message(n, THINKING);
}

int		philosopher_eat(int n, struct timeval *last_meal)
{
	sem_wait(forks);					// SEMAPHORE -1 fourchette
	if (simulation.stop == TRUE)
		return (FALSE);
	message(n, TAKING_FORK);				// notification
	sem_wait(forks);					// SEMAPHORE -1 fourchette
	if (simulation.stop == TRUE)
		return (FALSE);
	message(n, TAKING_FORK);				// notification
	simulation.meals_count[n - 1] += 1;
	message(n, EATING);						// notification
	gettimeofday(last_meal, NULL);			// enregistre l'heure du repas 
	simulation.meals_time[n - 1] = *last_meal;
	usleep(simulation.time_to_eat * 1000);	// mange
	sem_post(forks); 					// SEMAPHORE +1 fourchette
	sem_post(forks); 					// SEMAPHORE +1 fourchette
	return (TRUE);
}
*/

/*
void	*philosophing(void *arg)
{
	struct timeval last_meal;
	int n;

	last_meal = simulation.start;
	n = *(int*)arg + 1;
	while (simulation.stop == FALSE)							// zone critique mais le résultat n'est pas impacté négativement
	{
		philosopher_eat(n, &last_meal);
		philosopher_sleep(n);
		philosopher_think(n);
	}
	return (NULL);
}
*/

void	*philosophing(void *arg)
{
	struct timeval last_meal;
	int n;

	last_meal = simulation.start;
	n = *(int*)arg + 1;
	while (simulation.stop == FALSE)
	{
		sem_wait(forks);					// SEMAPHORE -1 fourchette
		message(n, TAKING_FORK);				// notification
		sem_wait(forks);					// SEMAPHORE -1 fourchette
		message(n, TAKING_FORK);				// notification

		simulation.meals_count[n - 1] += 1;
		message(n, EATING);						// notification
		sem_wait(eat);
		gettimeofday(&last_meal, NULL);			// enregistre l'heure du repas 
		sem_post(eat);
		simulation.meals_time[n - 1] = last_meal;
		usleep(simulation.time_to_eat * 1000);	// mange
		sem_post(forks); 					// SEMAPHORE +1 fourchette
		sem_post(forks); 					// SEMAPHORE +1 fourchette

		message(n, SLEEPING);
		usleep(simulation.time_to_sleep * 1000);
		message(n, THINKING);
		usleep(100); // try to not eat just after eating ?
	}
	return (NULL);
}
