/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/18 21:20:16 by user42            #+#    #+#             */
/*   Updated: 2020/07/18 21:28:15 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

sem_t *g_forks;

int		main(int ac, char *av[])
{
	int			*philosopher_ids;
	pthread_t	*thread_ids;

	if (simulation_init(&g_s, ac, av))
		return (EXIT_FAILURE);
	if ((g_forks = sem_open(SEMFORKS, O_CREAT, S_IRWXU, g_s.n)) == SEM_FAILED)
	{
		simulation_delete(NULL, NULL);
		return (EXIT_FAILURE);
	}
	philosopher_ids = malloc(sizeof(int*) * g_s.n);
	thread_ids = malloc(sizeof(pthread_t*) * g_s.n);
	create_threads(thread_ids, philosopher_ids);
	end_checker();
	wait_threads(thread_ids);
	simulation_delete(thread_ids, philosopher_ids);
	return (EXIT_SUCCESS);
}
