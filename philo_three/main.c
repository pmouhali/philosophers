/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/18 22:05:17 by user42            #+#    #+#             */
/*   Updated: 2020/07/18 22:13:36 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

struct timeval	g_last_meal;
unsigned int g_n_meals;
sem_t *g_forks;
sem_t *g_death;
sem_t *g_meals;

int		main(int ac, char *av[])
{
	unsigned int	i;
	int				*pids;

	if (simulation_init(&g_s, ac, av) || (pids = create_childs(g_s.n)) == NULL)
	{
		simulation_delete(NULL);
		return (EXIT_FAILURE);
	}
	sem_wait(g_death);
	i = -1;
	while (++i < g_s.n)
		kill(pids[i], SIGKILL);
	simulation_delete(pids);
	return (EXIT_SUCCESS);
}
