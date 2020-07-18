/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/18 22:06:23 by user42            #+#    #+#             */
/*   Updated: 2020/07/18 22:14:37 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	philosopher_sleep(int n)
{
	message(n, SLEEPING);
	usleep(g_s.time_to_sleep * 1000);
}

int		philosopher_eat(int n, struct timeval *last_meal)
{
	sem_wait(g_forks);
	message(n, TAKING_FORK);
	sem_wait(g_forks);
	message(n, TAKING_FORK);
	message(n, EATING);
	g_n_meals++;
	if (g_s.meals_option > 0 && g_n_meals == g_s.meals_option)
		sem_post(g_meals);
	gettimeofday(last_meal, NULL);
	usleep(g_s.time_to_eat * 1000);
	sem_post(g_forks);
	sem_post(g_forks);
	return (TRUE);
}

void	*philosophing(void *arg)
{
	unsigned int n;

	n = *(unsigned int*)arg;
	while (TRUE)
	{
		philosopher_eat(n, &g_last_meal);
		philosopher_sleep(n);
		message(n, THINKING);
		usleep(100);
	}
	return (NULL);
}
