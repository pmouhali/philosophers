/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmouhali <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/17 14:36:02 by pmouhali          #+#    #+#             */
/*   Updated: 2020/07/17 14:36:16 by pmouhali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void		take_forks(unsigned char n)
{
	g_simulation.table[left_fork(n)] = 0;
	g_simulation.table[right_fork(n)] = 0;
	message(n, TAKING_FORK);
	message(n, TAKING_FORK);
}


static void		putdown_forks(unsigned char n)
{
	g_simulation.table[left_fork(n)] = 1;
	g_simulation.table[right_fork(n)] = 1;
	pthread_mutex_unlock(&(g_simulation.mutexes[left_fork(n)]));
	pthread_mutex_unlock(&(g_simulation.mutexes[right_fork(n)]));
}

void	*philosophing(void *arg)
{
	unsigned char n;

	n = *(unsigned char*)arg + 1;
	while (g_simulation.stop == FALSE)
	{
		pthread_mutex_lock(&(g_simulation.mutexes[left_fork(n)]));
		if (g_simulation.table[right_fork(n)] == 1)
		{
			pthread_mutex_lock(&(g_simulation.mutexes[right_fork(n)]));
			take_forks(n);
			gettimeofday(&(g_simulation.meals_time[n - 1]), NULL);
			message(n, EATING);
			usleep(g_simulation.time_to_eat * 1000);
			putdown_forks(n);
			g_simulation.meals_count[n - 1] += 1;
			message(n, SLEEPING);
			usleep(g_simulation.time_to_sleep * 1000);
			message(n, THINKING);
		}
		else
			pthread_mutex_unlock(&(g_simulation.mutexes[left_fork(n)]));
	}
	return (NULL);
}

int		main(int ac, char *av[])
{
	pthread_t thread_ids[MAX_PHILOS + 1];

	if (simulation_init(&g_simulation, ac, av))
		return (EXIT_FAILURE);
	start_threads(thread_ids, g_simulation.n);
	while (g_simulation.stop == FALSE)
		watch_for_death();
	wait_threads(thread_ids, g_simulation.n);
	simulation_end(&g_simulation);
	return (EXIT_SUCCESS);
}
