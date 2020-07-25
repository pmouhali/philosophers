/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmouhali <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/17 14:30:32 by pmouhali          #+#    #+#             */
/*   Updated: 2020/07/18 12:34:11 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <string.h>
# include <stdint.h>
# include <sys/time.h>

# define FALSE 0
# define TRUE  1

# define MAX_PHILOS 200

# define USAGE "Usage: 4 required parameters, no negative numbers.\n"

enum	e_states
{
	TAKING_FORK,
	EATING,
	SLEEPING,
	THINKING,
	DEAD
};

typedef struct	s_simulation_data
{
	unsigned char	n;
	unsigned long	time_to_die;
	unsigned long	time_to_eat;
	unsigned long	time_to_sleep;

	unsigned char	stop;
	struct timeval	start;
	unsigned char	table[MAX_PHILOS + 1];
	pthread_mutex_t	forks[MAX_PHILOS + 1];
	pthread_mutex_t	eat_sync[MAX_PHILOS + 1];
	unsigned int	meals_option;
	unsigned char	meals_count[MAX_PHILOS + 1];
	struct timeval	meals_time[MAX_PHILOS + 1];

}				t_simulation_data;

t_simulation_data g_s;

unsigned long	get_time_in_ms(void);
unsigned long	elapsed_time(struct timeval t1, struct timeval t2);
int				simulation_init(t_simulation_data *sim, int ac, char **av);
int				ft_atoi(const char *str);
void			ft_sleep(unsigned int millisec);
void			simulation_end(t_simulation_data *simulation);
void			start_threads(pthread_t *tids, unsigned int n);
void			wait_threads(pthread_t *tids, unsigned int n);
void			watch_for_death(void);
void			*philosophing(void *arg);
void			message(int n, int state);
size_t			ft_strlen(const char *s);
unsigned int	left_fork(unsigned char i);
unsigned int	right_fork(unsigned char i);

#endif
