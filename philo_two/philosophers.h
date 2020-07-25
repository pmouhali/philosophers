/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/18 21:44:11 by user42            #+#    #+#             */
/*   Updated: 2020/07/18 21:57:18 by user42           ###   ########.fr       */
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
# include <sys/stat.h>
# include <fcntl.h>
# include <semaphore.h>

# define FALSE 0
# define TRUE  1

# define SEMFORKS "/keyforks"
# define SEMEAT "/keyeat"
# define MAX_PHILOS 200
# define USAGE "Usage: 4 parameters minimum required, no negative numbers.\n"

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
	unsigned int	n;
	unsigned long	time_to_die;
	unsigned long	time_to_eat;
	unsigned long	time_to_sleep;

	unsigned char	stop;
	struct timeval	start;
	unsigned int	meals_option;
	unsigned char	*meals_count;
	struct timeval	*meals_time;

}				t_simulation_data;

t_simulation_data g_s;
sem_t *g_forks;

unsigned long	elapsed_time(struct timeval t1, struct timeval t2);
unsigned long	get_time_in_ms(void);
size_t			ft_strlen(const char *s);
int				simulation_init(t_simulation_data *sim, int ac, char **av);
int				ft_atoi(const char *str);
void			ft_sleep(unsigned int millisec);
void			message(int n, int state);
void			simulation_delete(void *t1, void *t2);
void			create_threads(pthread_t *threads_ids, int *philosopher_ids);
void			*philosophing(void *arg);
void			wait_threads(pthread_t *thread_ids);
void			end_checker(void);

#endif
