/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_tools.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/18 12:28:50 by user42            #+#    #+#             */
/*   Updated: 2020/07/18 12:34:37 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	memset(sim->mutexes, 0, sizeof(pthread_mutex_t) * (sim->n + 1));
	i = -1;
	while (++i < sim->n)
		pthread_mutex_init(&(sim->mutexes[i]), NULL);
	gettimeofday(&(sim->start), NULL);
	i = -1;
	while (++i < sim->n)
		sim->meals_time[i] = sim->start;
	return (0);
}

void	simulation_end(t_simulation_data *g_s)
{
	unsigned int i;

	i = -1;
	while (++i < g_s->n)
		pthread_mutex_destroy(&(g_s->mutexes[i]));
}

void	start_threads(pthread_t *tids, unsigned int n)
{
	unsigned char	number[MAX_PHILOS + 1];
	unsigned int	i;

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
	unsigned char	i;
	struct timeval	now;

	i = -1;
	while (++i < g_s.n && g_s.stop == FALSE)
	{
		gettimeofday(&now, NULL);
		if (g_s.table[left_fork(i + 1)] && g_s.table[right_fork(i + 1)])
		{
			pthread_mutex_lock(&(g_s.mutexes[left_fork(i + 1)]));
			if (elapsed_time(g_s.meals_time[i], now) > g_s.time_to_die)
			{
				g_s.stop = TRUE;
				message(i + 1, DEAD);
			}
			pthread_mutex_unlock(&(g_s.mutexes[left_fork(i + 1)]));
		}
	}
	if (g_s.meals_option == 0)
		return ;
	i = 0;
	while (g_s.meals_count[i] >= g_s.meals_option)
		i++;
	if (i == g_s.n)
		g_s.stop = TRUE;
}
