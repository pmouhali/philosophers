/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophing_routine.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/18 21:34:02 by user42            #+#    #+#             */
/*   Updated: 2020/07/27 20:36:18 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	meals_checker(void)
{
	unsigned int i;

	if (g_s.meals_option <= 0)
		return ;
	i = 0;
	while (g_s.meals_count[i] >= g_s.meals_option)
		i++;
	g_s.stop = i == g_s.n ? TRUE : FALSE;
}

void		end_checker(void)
{
	unsigned int	i;
	struct timeval	now;

	while (g_s.stop == FALSE && (i = -1))
	{
		while (++i < g_s.n)
		{
			sem_wait(g_s.eating[i]);
			gettimeofday(&now, NULL);
			if (elapsed_time(g_s.meals_time[i], now) > g_s.time_to_die)
			{
				g_s.stop = TRUE;
				message(i + 1, DEAD);
				i = -1;
				while (++i < g_s.n)
				{
					sem_post(g_forks);
					sem_post(g_s.eating[i]);
				}
				return ;
			}
			sem_post(g_s.eating[i]);
		}
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
		sem_wait(g_s.eating[*(int*)arg]);
		gettimeofday(&last_meal, NULL);
		sem_post(g_s.eating[*(int*)arg]);
		g_s.meals_time[*(int*)arg] = last_meal;
		ft_sleep(g_s.time_to_eat);
		sem_post(g_forks);
		sem_post(g_forks);
		message(*(int*)arg + 1, SLEEPING);
		ft_sleep(g_s.time_to_sleep);
		message(*(int*)arg + 1, THINKING);
		usleep(90);
	}
	return (NULL);
}
