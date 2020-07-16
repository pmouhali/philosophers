// 42 Header

#include "philosophers.h"

static void		take_forks(unsigned char n)
{
	simulation.table[LEFT_FORK(n)] = 0;
	simulation.table[RIGHT_FORK(n)] = 0;
	message(n, TAKING_FORK);
	message(n, TAKING_FORK);
}


static void		putdown_forks(unsigned char n)
{
	simulation.table[LEFT_FORK(n)] = 1;
	simulation.table[RIGHT_FORK(n)] = 1;
	pthread_mutex_unlock(&(simulation.mutexes[LEFT_FORK(n)]));
	pthread_mutex_unlock(&(simulation.mutexes[RIGHT_FORK(n)]));
}

void	*philosophing(void *arg)
{
	unsigned char n;

	n = *(unsigned char*)arg + 1;
	while (simulation.stop == FALSE)
	{
		pthread_mutex_lock(&(simulation.mutexes[LEFT_FORK(n)]));
		if (simulation.table[RIGHT_FORK(n)] == 1)
		{
			pthread_mutex_lock(&(simulation.mutexes[RIGHT_FORK(n)]));
			take_forks(n);
			gettimeofday(&(simulation.meals_time[n - 1]), NULL);
			message(n, EATING);
			usleep(simulation.time_to_eat * 1000);
			putdown_forks(n);
			simulation.meals_count[n - 1] += 1;
			message(n, SLEEPING);
			usleep(simulation.time_to_sleep * 1000);
			message(n, THINKING);
		}
		else
			pthread_mutex_unlock(&(simulation.mutexes[LEFT_FORK(n)]));
	}
	return (NULL);
}

int		main(int ac, char *av[])
{
	pthread_t thread_ids[MAX_PHILOS + 1];

	if (simulation_init(&simulation, ac, av))
		return (EXIT_FAILURE);
	start_threads(thread_ids, simulation.n);
	while (simulation.stop == FALSE)
		watch_for_death();
	wait_threads(thread_ids, simulation.n);
	simulation_end(&simulation);
	return (EXIT_SUCCESS);
}
