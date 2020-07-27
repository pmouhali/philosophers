/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/18 21:26:02 by user42            #+#    #+#             */
/*   Updated: 2020/07/18 21:43:50 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void		create_threads(pthread_t *thread_ids, int *philosopher_ids)
{
	unsigned int i;

	i = 0;
	while (i < g_s.n)
	{
		philosopher_ids[i] = i;
		pthread_create(&thread_ids[i], NULL, philosophing, &philosopher_ids[i]);
		i++;
	}
}

void		wait_threads(pthread_t *thread_ids)
{
	unsigned int i;

	i = 0;
	while (i < g_s.n)
	{
		pthread_join(thread_ids[i], NULL);
		i++;
	}
}
