// 42 Header

#include "philosophers.h"

sem_t *semaphore;

void	check_for_death(int n, struct timeval last_meal)
{
	struct timeval now;

	gettimeofday(&now, NULL);
	if (elapsed_time(last_meal, now) > simulation.time_to_die)
	{
		sem_wait(semaphore); // SEMAPHORE
		simulation.stop = TRUE;
		sem_post(semaphore); // SEMAPHORE
		message(n, DEAD);
	}
}

void	check_for_end_of_simulation(void)
{
	unsigned int i;

	if (simulation.stop == TRUE)
		pthread_exit(NULL);
	if (simulation.meals_per_philosopher_before_stop > 0)
	{
		i = 0;
		while (simulation.meals_per_philosopher[i] >= simulation.meals_per_philosopher_before_stop)
			i++;
		if (i == simulation.n_philosophers)
		{
			simulation.stop = TRUE;
			pthread_exit(NULL);
		}
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
	sem_wait(semaphore); // SEMAPHORE
	if (simulation.forks >= 2)
	{	
		simulation.forks -= 2;
		simulation.meals_per_philosopher[n - 1] += 1;
		sem_post(semaphore); // SEMAPHORE
		message(n, TAKING_FORK);
		message(n, EATING);
		gettimeofday(last_meal, NULL);
		usleep(simulation.time_to_eat * 1000);
		sem_wait(semaphore); // SEMAPHORE
		simulation.forks += 2;
		sem_post(semaphore); // SEMAPHORE
		return (TRUE);
	}
	sem_post(semaphore); // SEMAPHORE
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
	pthread_exit(NULL);
}

int		main(int ac, char *av[])
{
	unsigned int i;
	int *philosopher_ids;
	pthread_t *thread_ids;

	if (simulation_init(&simulation, ac, av))
		return (EXIT_FAILURE);
	if ((semaphore = sem_open(SEMKEY, O_CREAT, S_IRWXU, 1)) == SEM_FAILED)
	{
		simulation_delete(NULL, NULL, NULL);
		return (EXIT_FAILURE);
	}
	sem_unlink(SEMKEY);
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
	simulation_delete(thread_ids, philosopher_ids, semaphore);
	return (EXIT_SUCCESS);
}
