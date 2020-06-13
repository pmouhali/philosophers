// 42 Header

#include "philosophers.h"

static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void	check_for_death(int n, struct timeval last_meal)
{
	struct timeval now;

	gettimeofday(&now, NULL);
	if (elapsed_time(last_meal, now) > simulation.time_to_die)
	{
		pthread_mutex_lock(&mutex);
		simulation.stop = TRUE;
		pthread_mutex_unlock(&mutex);
		message(n, DEAD);
	}
}

void	check_for_end_of_simulation(void)
{
	int i;

	if (simulation.stop == TRUE)
		return ;
	if (simulation.meals_per_philosopher_before_stop > 0)
	{
		i = 0;
		while (simulation.meals_per_philosopher[i] >= simulation.meals_per_philosopher_before_stop)
			i++;
		if (i == simulation.n_philosophers)
			simulation.stop = TRUE;
	}
}

void	philosopher_sleep(int n)
{
	check_for_end_of_simulation();
	message(n, SLEEPING);
	usleep(simulation.time_to_sleep * 1000);
}

void	philosopher_think(int n)
{
	check_for_end_of_simulation();
	message(n, THINKING);
}

int		philosopher_eat(int n, struct timeval *last_meal)
{
	pthread_mutex_lock(&mutex);
	if (simulation.table[LEFT_FORK(n)] && simulation.table[RIGHT_FORK(n)])
	{
		simulation.table[LEFT_FORK(n)] = 0;
		simulation.table[RIGHT_FORK(n)] = 0;
		simulation.meals_per_philosopher[n - 1] += 1;
		pthread_mutex_unlock(&mutex);
		message(n, TAKING_FORK);
		message(n, EATING);
		gettimeofday(last_meal, NULL);
		usleep(simulation.time_to_eat * 1000);
		pthread_mutex_lock(&mutex);
		simulation.table[LEFT_FORK(n)] = 1;
		simulation.table[RIGHT_FORK(n)] = 1;
		pthread_mutex_unlock(&mutex);
		return (TRUE);
	}
	pthread_mutex_unlock(&mutex);
	return (FALSE);
}

void	*philosophing(void *arg)
{
	struct timeval last_meal;
	int n;

	last_meal = simulation.start;
	n = *(int*)arg + 1;
	while (simulation.stop == FALSE)							// zone critique mais le résultat n'est pas impacté négativement
	{
		if (philosopher_eat(n, &last_meal))
		{
			philosopher_sleep(n);
			philosopher_think(n);
		}
		else
			check_for_death(n, last_meal);
	}
	return (NULL);
}

int		main(int ac, char *av[])
{
	int i;
	int *philosopher_ids;
	pthread_t *thread_ids;

	if (simulation_init(&simulation, ac, av))
		return (EXIT_FAILURE);
	philosopher_ids = malloc(sizeof(int*) * simulation.n_philosophers);
	thread_ids = malloc(sizeof(pthread_t*) * simulation.n_philosophers);
	i = -1;
	while (++i < simulation.n_philosophers)
	{
		philosopher_ids[i] = i;
		pthread_create(&thread_ids[i], NULL, philosophing, &philosopher_ids[i]);
	}
	i = -1;
	while (++i < simulation.n_philosophers)
		pthread_join(thread_ids[i], NULL);
	free(simulation.table);
	free(simulation.meals_per_philosopher);
	free(philosopher_ids);
	free(thread_ids);
	pthread_mutex_destroy(&mutex);
	return (EXIT_SUCCESS);
}
