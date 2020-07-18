/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elapsed_time.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/18 21:19:37 by user42            #+#    #+#             */
/*   Updated: 2020/07/18 21:19:52 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

unsigned long	elapsed_time(struct timeval t1, struct timeval t2)
{
	unsigned long timestamp1;
	unsigned long timestamp2;

	timestamp1 = (t1.tv_usec / 1000 + t1.tv_sec * 1000);
	timestamp2 = (t2.tv_usec / 1000 + t2.tv_sec * 1000);
	if (timestamp1 >= timestamp2)
		return (0);
	return (timestamp2 - timestamp1);
}
