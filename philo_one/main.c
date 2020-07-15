// 42 Header

#include "philosophers.h"

//static pthread_mutex_t death = PTHREAD_MUTEX_INITIALIZER;

///* VERSION ou il repose la fourchette si l'autre n'est pas dispo
void	*philosophing(void *arg)
{
	unsigned char n;

	n = *(unsigned char*)arg + 1;
	while (simulation.stop == FALSE)
	{
		// try to eat
		pthread_mutex_lock(&(simulation.mutexes[LEFT_FORK(n)]));
		if (simulation.table[RIGHT_FORK(n)] == 1)
		{
			pthread_mutex_lock(&(simulation.mutexes[RIGHT_FORK(n)]));
			simulation.table[LEFT_FORK(n)] = 0;
			simulation.table[RIGHT_FORK(n)] = 0;
			message(n, TAKING_FORK);
			message(n, TAKING_FORK);

			gettimeofday(&(simulation.meals_time[n - 1]), NULL);
			message(n, EATING);
			usleep(simulation.time_to_eat * 1000);

			simulation.table[LEFT_FORK(n)] = 1;
			simulation.table[RIGHT_FORK(n)] = 1;
			pthread_mutex_unlock(&(simulation.mutexes[LEFT_FORK(n)]));
			pthread_mutex_unlock(&(simulation.mutexes[RIGHT_FORK(n)]));

			simulation.meals_per_philosopher[n - 1] += 1;
			// sleep and think if eat success
			message(n, SLEEPING);
			usleep(simulation.time_to_sleep * 1000);
			message(n, THINKING);
		}
		else
			pthread_mutex_unlock(&(simulation.mutexes[LEFT_FORK(n)]));
	}
	return (NULL);
}
//*/

/* VERSION sans verification: ne fonctionne pas du tout ! 
void	*philosophing(void *arg)
{
	unsigned char n;

	n = *(unsigned char*)arg + 1;
	while (simulation.stop == FALSE)
	{
		// try to eat
		pthread_mutex_lock(&(simulation.mutexes[LEFT_FORK(n)]));
		message(n, TAKING_FORK);
		pthread_mutex_lock(&(simulation.mutexes[RIGHT_FORK(n)]));
		message(n, TAKING_FORK);

		gettimeofday(&(simulation.meals_time[n - 1]), NULL);
		message(n, EATING);
		usleep(simulation.time_to_eat * 1000);

		pthread_mutex_unlock(&(simulation.mutexes[LEFT_FORK(n)]));
		pthread_mutex_unlock(&(simulation.mutexes[RIGHT_FORK(n)]));

		simulation.meals_per_philosopher[n - 1] += 1;
		// sleep and think if eat success
		message(n, SLEEPING);
		usleep(simulation.time_to_sleep * 1000);
		message(n, THINKING);
	}
	return (NULL);
}
*/

int		main(int ac, char *av[])
{
	unsigned long long elapsed_t;
	unsigned char i;
	unsigned char philosopher_ids[MAX_PHILOS + 1];
	pthread_t thread_ids[MAX_PHILOS + 1];

	if (simulation_init(&simulation, ac, av))
		return (EXIT_FAILURE);
	// START THREADS
	i = -1;
	while (++i < simulation.n_philosophers)
	{
		philosopher_ids[i] = i;
		pthread_create(&thread_ids[i], NULL, philosophing, &philosopher_ids[i]);
	}
	
	struct timeval now;
	// DEATH CHECK
	while (simulation.stop == FALSE)
	{
		i = -1;
		while (++i < simulation.n_philosophers && simulation.stop == FALSE)
		{
			gettimeofday(&now, NULL);
			if (simulation.table[LEFT_FORK(i + 1)] && simulation.table[RIGHT_FORK(i + 1)])
			{
				pthread_mutex_lock(&(simulation.mutexes[LEFT_FORK(i + 1)]));
				elapsed_t = elapsed_time(simulation.meals_time[i], now);
				if (elapsed_t > simulation.time_to_die)
				{
					simulation.stop = TRUE;
					message(i + 1, DEAD);
				}
				pthread_mutex_unlock(&(simulation.mutexes[LEFT_FORK(i + 1)]));
			}
		}
		if (simulation.meals_per_philosopher_before_stop > 0)
		{
			i = 0;
			while (simulation.meals_per_philosopher[i] >= simulation.meals_per_philosopher_before_stop)
				i++;
			if (i == simulation.n_philosophers)
				simulation.stop = TRUE;
		}
	}

	// WAIT THREADS
	i = -1;
	while (++i < simulation.n_philosophers)
		pthread_join(thread_ids[i], NULL);
	simulation_end(&simulation);

//	pthread_mutex_destroy(&mutex);
	return (EXIT_SUCCESS);
}
