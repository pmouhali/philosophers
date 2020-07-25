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

void	watch_for_death(void)
{
	unsigned char	i;
	struct timeval	now;

	i = -1;
	while (++i < g_s.n && g_s.stop == FALSE)
	{
		pthread_mutex_lock(&(g_s.eat_sync[i]));	
		gettimeofday(&now, NULL);
		if (elapsed_time(g_s.meals_time[i], now) > g_s.time_to_die)
		{
			g_s.stop = TRUE;
			message(i + 1, DEAD);
		}
		pthread_mutex_unlock(&(g_s.eat_sync[i]));	
	}
	if (g_s.meals_option == 0)
		return ;
	i = 0;
	while (g_s.meals_count[i] >= g_s.meals_option)
		i++;
	if (i == g_s.n)
		g_s.stop = TRUE;
}
