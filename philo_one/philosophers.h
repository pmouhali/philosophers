/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmouhali <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/17 14:30:32 by pmouhali          #+#    #+#             */
/*   Updated: 2020/07/17 14:38:44 by pmouhali         ###   ########.fr       */
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

# define USAGE "Usage: ./philo_one <philosophers> <time to die> <time to eat> <time to sleep> <Optional: how many time each must eat for the simulation to stop>\n"

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
	pthread_mutex_t	mutexes[MAX_PHILOS + 1];
	unsigned int	meals_option;
	unsigned char	meals_count[MAX_PHILOS + 1];
	struct timeval	meals_time[MAX_PHILOS + 1];

}				t_simulation_data;

t_simulation_data g_simulation;

int				simulation_init(t_simulation_data *sim, int ac, char **av);
void    		simulation_end(t_simulation_data *simulation);
void			start_threads(pthread_t *tids, unsigned int n);
void			wait_threads(pthread_t *tids, unsigned int n);
void			watch_for_death(void);

unsigned int	left_fork(unsigned char i);
unsigned int	right_fork(unsigned char i);
void			*philosophing(void *arg);

unsigned long long	elapsed_time(struct timeval t1, struct timeval t2);
void			message(int n, int state);
size_t			ft_strlen(const char *s);
int				ft_atoi(const char *str);

#endif
