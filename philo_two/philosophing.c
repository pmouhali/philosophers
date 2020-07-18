/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/18 21:34:02 by user42            #+#    #+#             */
/*   Updated: 2020/07/18 21:42:08 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	meals_checker(void)
{
	unsigned int i;

	i = 0;
	while (g_s.meals_count[i] >= g_s.meals_option)
		i++;
	g_s.stop = i == g_s.n ? TRUE : FALSE;
}

void		end_checker(void)
{
	unsigned int	i;
	struct timeval	now;

	while (g_s.stop == FALSE)
	{
		i = -1;
		while (++i < g_s.n)
		{
			sem_wait(g_eat);
			gettimeofday(&now, NULL);
			sem_post(g_eat);
			if (elapsed_time(g_s.meals_time[i], now) > g_s.time_to_die)
			{
				g_s.stop = TRUE;
				message(i + 1, DEAD);
				i = -1;
				while (++i < g_s.n)
					sem_post(g_forks);
				return ;
			}
		}
		if (g_s.meals_option > 0)
			meals_checker();
	}
}

void		*philosophing(void *arg)
{
	struct timeval last_meal;

	last_meal = g_s.start;
	while (g_s.stop == FALSE)
	{
		sem_wait(g_forks);
		message(*(int*)arg + 1, TAKING_FORK);
		sem_wait(g_forks);
		message(*(int*)arg + 1, TAKING_FORK);
		g_s.meals_count[*(int*)arg] += 1;
		message(*(int*)arg + 1, EATING);
		sem_wait(g_eat);
		gettimeofday(&last_meal, NULL);
		sem_post(g_eat);
		g_s.meals_time[*(int*)arg] = last_meal;
		usleep(g_s.time_to_eat * 1000);
		sem_post(g_forks);
		sem_post(g_forks);
		message(*(int*)arg + 1, SLEEPING);
		usleep(g_s.time_to_sleep * 1000);
		message(*(int*)arg + 1, THINKING);
		usleep(100);
	}
	return (NULL);
}
