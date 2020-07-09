// 42 HEADER

#include "philosophers.h"

int		simulation_init(t_simulation_data *sim, int ac, char **av)
{
//	unsigned int i;

	if (ac < 5 || (sim->n_philosophers = ft_atoi(av[1])) > THREADS_MAX)
	{
		write(1, USAGE, ft_strlen(USAGE));
		return (1);
	}
	sim->time_to_die = ft_atoi(av[2]);
	sim->time_to_eat = ft_atoi(av[3]);
	sim->time_to_sleep = ft_atoi(av[4]);
	sim->meals_per_philosopher_before_stop = ac > 5 ? ft_atoi(av[5]) : 0;
	sim->stop = FALSE;
//	sim->meals_per_philosopher = malloc(sizeof(char) * (sim->n_philosophers + 1));
//	memset(sim->meals_per_philosopher, 0, sizeof(char) * (sim->n_philosophers + 1));
	gettimeofday(&(sim->start), NULL);
//	sim->philosophers_last_meals = malloc(sizeof(*(sim->philosophers_last_meals)) * (sim->n_philosophers + 1));
//	i = 0;
//	while (i < sim->n_philosophers)
//	{
//		sim->philosophers_last_meals[i] = sim->start;
//		i++;
//	}
	return (0);
}

void	simulation_delete(void *t1, sem_t *forks, sem_t *death)
{
	sem_unlink(SEMFORKS);
	sem_close(forks);
	sem_unlink(SEMDEATH);
	sem_close(death);
//	free(simulation.meals_per_philosopher); USELESS
//	free(simulation.philosophers_last_meals); USELESS
	free(t1);
}

int		*create_childs(unsigned int n)
{
	int *pids;
	unsigned int i;

	if ((pids = malloc(sizeof(int) * n)) == NULL)
		return (NULL);
	i = -1;
	while (++i < n)
	{
		// create a child with a n° of philosopher, the child will lauch a thread with the philosophing routine
		pids[i] = fork();
		if (pids[i] == 0)
		{
			child_process_actions(i + 1);
			return (NULL);
		}
	}
	return (pids);
}

void	child_process_actions(unsigned int n)
{
	pthread_t tid;
	struct timeval now;

	last_meal = simulation.start;
	// launch thread && join thread ?
	pthread_create(&tid, NULL, philosophing, &n);
	// keep track of death
	// if death post on semaphore DEATH
	while (TRUE)
	{
		gettimeofday(&now, NULL);
		if (elapsed_time(last_meal, now) > simulation.time_to_die)
		{
			message(n, DEAD);
			sem_post(death);
		}
		usleep(5); // useful ?
	}
}

/*
void	create_threads(pthread_t *thread_ids, int *philosopher_ids)
{
	unsigned int i;

	i = 0;
	while (i < simulation.n_philosophers)
	{
		philosopher_ids[i] = i;
		pthread_create(&thread_ids[i], NULL, philosophing, &philosopher_ids[i]);
		i++;
	}
}

void	wait_threads(pthread_t *thread_ids)
{
	unsigned int i;

	i = 0;
	while (i < simulation.n_philosophers)
	{
		pthread_join(thread_ids[i], NULL);
		i++;
	}
}
*/
