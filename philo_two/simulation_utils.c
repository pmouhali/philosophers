/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/18 21:26:02 by user42            #+#    #+#             */
/*   Updated: 2020/07/27 20:38:33 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	clear_semaphores(void)
{
	unsigned int	i;
	char			*semkey;

	sem_unlink(SEMFORKS);
	sem_close(g_forks);
	i = 0;
	while (i < g_s.n)
	{
		semkey = ft_strjoin_free("eating_", ft_itoa(i), 2);
		sem_unlink(semkey);
		sem_close(g_s.eating[i]);
		free(semkey);
		i++;
	}
}

static void	create_eating_semaphores(t_simulation_data *s)
{
	unsigned int	i;
	char			*semkey;

	i = 0;
	while (i < s->n)
	{
		semkey = ft_strjoin_free("eating_", ft_itoa(i), 2);
		s->eating[i] = sem_open(semkey, O_CREAT, 0666, 1);
		free(semkey);
		i++;
	}
}

static int	validates_parameters(t_simulation_data *sim, int ac, char **av)
{
	if (ac < 5 || (sim->n = ft_atoi(av[1])) > MAX_PHILOS)
	{
		write(1, USAGE, ft_strlen(USAGE));
		return (1);
	}
	sim->time_to_die = ft_atoi(av[2]);
	sim->time_to_eat = ft_atoi(av[3]);
	sim->time_to_sleep = ft_atoi(av[4]);
	sim->meals_option = ac > 5 ? ft_atoi(av[5]) : 0;
	return (0);
}

int			simulation_init(t_simulation_data *sim, int ac, char **av)
{
	unsigned int i;

	if (validates_parameters(sim, ac, av))
		return (1);
	sim->stop = FALSE;
	sim->meals_count = malloc(sizeof(char) * (sim->n + 1));
	memset(sim->meals_count, 0, sizeof(char) * (sim->n + 1));
	sim->eating = malloc(sizeof(sem_t) * (sim->n + 1));
	clear_semaphores();
	memset(sim->eating, 0, sizeof(sem_t) * (sim->n + 1));
	create_eating_semaphores(sim);
	sim->meals_time = malloc(sizeof(*(sim->meals_time)) * (sim->n + 1));
	gettimeofday(&(sim->start), NULL);
	i = 0;
	while (i < sim->n)
	{
		sim->meals_time[i] = sim->start;
		i++;
	}
	return (0);
}

void		simulation_delete(void *t1, void *t2)
{
	clear_semaphores();
	free(g_s.meals_count);
	free(g_s.meals_time);
	free(g_s.eating);
	free(t1);
	free(t2);
}
