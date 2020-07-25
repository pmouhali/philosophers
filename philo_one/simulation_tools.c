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

static int		validates_parameters(t_simulation_data *sim, int ac, char **av)
{
	int r;

	r = 0;
	if (ac < 5)
		r = 1;
	else if ((sim->n = ft_atoi(av[1])) > MAX_PHILOS)
		r = 1;
	sim->time_to_die = ft_atoi(av[2]);
	sim->time_to_eat = ft_atoi(av[3]);
	sim->time_to_sleep = ft_atoi(av[4]);
	sim->meals_option = ac > 5 ? ft_atoi(av[5]) : 0;
	if (r)
		write(1, USAGE, ft_strlen(USAGE));
	return (r);
}

int		simulation_init(t_simulation_data *sim, int ac, char **av)
{
	unsigned int i;

	simulation_end(&g_s);
	if (validates_parameters(sim, ac, av))
		return (1);
	sim->stop = FALSE;
	memset(sim->table, 0, sizeof(unsigned char) * MAX_PHILOS);
	memset(sim->table, 1, sizeof(char) * sim->n);
	memset(sim->meals_count, 0, sizeof(char) * (sim->n + 1));
	memset(sim->forks, 0, sizeof(pthread_mutex_t) * (sim->n + 1));
	memset(sim->eat_sync, 0, sizeof(pthread_mutex_t) * (sim->n + 1));
	i = -1;
	while (++i < sim->n)
		pthread_mutex_init(&(sim->forks[i]), NULL);
	i = -1;
	while (++i < sim->n)
		pthread_mutex_init(&(sim->eat_sync[i]), NULL);
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
		pthread_mutex_destroy(&(g_s->forks[i]));
	i = -1;
	while (++i < g_s->n)
		pthread_mutex_destroy(&(g_s->eat_sync[i]));
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
