/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fcn_forks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmouhali <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/17 14:33:08 by pmouhali          #+#    #+#             */
/*   Updated: 2020/07/18 12:37:26 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

unsigned int	left_fork(unsigned char i)
{
	return (i - 1 == g_s.n - 1 ? 0 : (i - 1) + 1);
}

unsigned int	right_fork(unsigned char i)
{
	return (i - 1 == 0 && g_s.n == 1 ? 1 : (i - 1));
}
