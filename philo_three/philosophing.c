/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/18 22:06:23 by user42            #+#    #+#             */
/*   Updated: 2020/07/27 21:04:00 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	philosopher_sleep(int n)
{
	message(n, SLEEPING);
	ft_sleep(g_s.time_to_sleep);
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
	sem_wait(g_eating);
	gettimeofday(last_meal, NULL);
	ft_sleep(g_s.time_to_eat);
	sem_post(g_eating);
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
		ft_sleep(5);
	}
	return (NULL);
}
