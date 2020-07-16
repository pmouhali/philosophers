// 42 HEADER

#include "philosophers.h"

int		simulation_init(t_simulation_data *sim, int ac, char **av)
{
	unsigned int i;

	if (ac < 5 || (sim->n = ft_atoi(av[1])) > MAX_PHILOS)
	{
		write(1, USAGE, ft_strlen(USAGE));
		return (1);
	}
	sim->time_to_die = ft_atoi(av[2]);
	sim->time_to_eat = ft_atoi(av[3]);
	sim->time_to_sleep = ft_atoi(av[4]);
	sim->meals_option = ac > 5 ? ft_atoi(av[5]) : 0;
	sim->stop = FALSE;
	memset(sim->table, 0, sizeof(unsigned char) * MAX_PHILOS);
	memset(sim->table, 1, sizeof(char) * sim->n);
	memset(sim->meals_count, 0, sizeof(char) * (sim->n + 1));
	gettimeofday(&(sim->start), NULL);
	i = -1;
	while (++i < sim->n)
		sim->meals_time[i] = sim->start;
	i = -1;
	while (++i < sim->n)
		pthread_mutex_init(&(sim->mutexes[i]), NULL);
	return (0);
}

void	simulation_end(t_simulation_data *simulation)
{
	unsigned int i;

	i = -1;
	while (++i < simulation->n)
		pthread_mutex_destroy(&(simulation->mutexes[i]));
}

void	start_threads(pthread_t *tids, unsigned int n)
{
	unsigned char number[MAX_PHILOS + 1];
	unsigned int i;

	i = -1;                                                                      
	while (++i < n)                                                   
	{                                                                            
		number[i] = i;                                                  
		pthread_create(&tids[i], NULL, philosophing, &number[i]); 
	} 
}

void	wait_threads(pthread_t *tids, unsigned int n)
{
	unsigned int i;

	i = -1;                                                                      
	while (++i < n)                                                   
		pthread_join(tids[i], NULL);
}

void	watch_for_death(void)
{
	unsigned char i;
	struct timeval now;

	i = -1;
	while (++i < simulation.n && simulation.stop == FALSE) 
	{
		gettimeofday(&now, NULL);
		if (simulation.table[LEFT_FORK(i + 1)] && simulation.table[RIGHT_FORK(i + 1)])
		{ 
			pthread_mutex_lock(&(simulation.mutexes[LEFT_FORK(i + 1)]));
			if (elapsed_time(simulation.meals_time[i], now) > simulation.time_to_die)
			{
				simulation.stop = TRUE;
				message(i + 1, DEAD);
			}
			pthread_mutex_unlock(&(simulation.mutexes[LEFT_FORK(i + 1)]));
		}
	}
	if (simulation.meals_option == 0)
		return ;
	i = 0;
	while (simulation.meals_count[i] >= simulation.meals_option)
		i++;
	if (i == simulation.n)
		simulation.stop = TRUE;
}
