/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmouhali <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/17 14:36:02 by pmouhali          #+#    #+#             */
/*   Updated: 2020/07/27 20:23:46 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	take_forks_and_eat(unsigned char n)
{
	pthread_mutex_lock(&(g_s.eat_sync[n - 1]));
	g_s.table[left_fork(n)] = 0;
	g_s.table[right_fork(n)] = 0;
	message(n, TAKING_FORK);
	message(n, TAKING_FORK);
	gettimeofday(&(g_s.meals_time[n - 1]), NULL);
	pthread_mutex_unlock(&(g_s.eat_sync[n - 1]));
	message(n, EATING);
	ft_sleep(g_s.time_to_eat);
}

static void	putdown_forks(unsigned char n)
{
	g_s.table[left_fork(n)] = 1;
	g_s.table[right_fork(n)] = 1;
	pthread_mutex_unlock(&(g_s.forks[left_fork(n)]));
	pthread_mutex_unlock(&(g_s.forks[right_fork(n)]));
}

void		*philosophing(void *arg)
{
	unsigned char n;

	n = *(unsigned char*)arg + 1;
	while (g_s.stop == FALSE)
	{
		pthread_mutex_lock(&(g_s.forks[left_fork(n)]));
		if (g_s.table[right_fork(n)] == 1)
		{
			pthread_mutex_lock(&(g_s.forks[right_fork(n)]));
			take_forks_and_eat(n);
			putdown_forks(n);
			g_s.meals_count[n - 1] += 1;
			message(n, SLEEPING);
			ft_sleep(g_s.time_to_sleep);
			message(n, THINKING);
			usleep(90);
		}
		else
			pthread_mutex_unlock(&(g_s.forks[left_fork(n)]));
	}
	return (NULL);
}

int			main(int ac, char *av[])
{
	pthread_t thread_ids[MAX_PHILOS + 1];

	memset(&g_s, 0, sizeof(t_simulation_data));
	if (simulation_init(&g_s, ac, av))
		return (EXIT_FAILURE);
	start_threads(thread_ids, g_s.n);
	while (g_s.stop == FALSE)
		watch_for_death();
	wait_threads(thread_ids, g_s.n);
	simulation_end(&g_s);
	return (EXIT_SUCCESS);
}
