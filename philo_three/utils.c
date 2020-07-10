// 42 HEADER

#include "philosophers.h"

int		simulation_init(t_simulation_data *sim, int ac, char **av)
{
	pthread_t tid;

	if (ac < 5 || (sim->n_philosophers = ft_atoi(av[1])) > THREADS_MAX)
	{
		write(1, USAGE, ft_strlen(USAGE));
		return (1);
	}
	sim->time_to_die = ft_atoi(av[2]);
	sim->time_to_eat = ft_atoi(av[3]);
	sim->time_to_sleep = ft_atoi(av[4]);
	sim->meals_per_philosopher_before_stop = ac > 5 ? ft_atoi(av[5]) : 0;
	gettimeofday(&(sim->start), NULL);
	if ((forks = sem_open(SEMFORKS, O_CREAT, S_IRWXU, sim->n_philosophers)) == SEM_FAILED
		|| (death = sem_open(SEMDEATH, O_CREAT, S_IRWXU, 0)) == SEM_FAILED
			|| (meals = sem_open(SEMMEALS, O_CREAT, S_IRWXU, 0)) == SEM_FAILED)
		return (1);
	if (sim->meals_per_philosopher_before_stop > 0)
		pthread_create(&tid, NULL, count_meals_routine, NULL);
	return (0);
}

void	simulation_delete(void *t1)
{
	free(t1);
	sem_unlink(SEMFORKS);
	sem_close(forks);
	sem_unlink(SEMDEATH);
	sem_close(death);
	sem_unlink(SEMMEALS);
	sem_close(death);
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
	n_meals = 0;
	pthread_create(&tid, NULL, philosophing, &n);
	while (TRUE)
	{
		gettimeofday(&now, NULL);
		if (elapsed_time(last_meal, now) > simulation.time_to_die)
		{
			message(n, DEAD);
			sem_post(death);
			return ;
		}
		usleep(100); // useful ?
	}
}

void	*count_meals_routine(void *arg)
{
	(void)arg;
	unsigned int i;

	i = 0;
	while (i < simulation.n_philosophers)
	{
		sem_wait(meals);
		i++;
	}
	sem_post(death);
	return (NULL);
}
