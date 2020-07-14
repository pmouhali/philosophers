// 42 header

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>
#include <stdint.h>
#include <sys/time.h>

#include <stdio.h>

#define FALSE 0
#define TRUE  1

#define MAX_PHILOS 200

#define USAGE "Usage: ./philoX <philosophers> <time to die> <time to eat> <time to sleep> <Optional: how many time each must eat for the simulation to stop>\n"

#define LEFT_FORK(n)  n - 1 == simulation.n_philosophers - 1 ? 0 : (n - 1) + 1
#define RIGHT_FORK(n) n - 1 == 0 && simulation.n_philosophers == 1 ? 1 : (n - 1)

enum	e_states
{
	TAKING_FORK,
	EATING,
	GIVING_FORK,
	SLEEPING,
	THINKING,
	DEAD
};

typedef struct	s_simulation_data
{
	unsigned char	n_philosophers;                                                
	unsigned long	time_to_die;
	unsigned long	time_to_eat;
	unsigned long	time_to_sleep;  

	unsigned char	stop;
	unsigned char	table[MAX_PHILOS + 1];
	pthread_mutex_t	mutexes[MAX_PHILOS + 1];
	unsigned int	meals_per_philosopher_before_stop;
	unsigned char	meals_per_philosopher[MAX_PHILOS + 1];
	struct timeval	meals_time[MAX_PHILOS + 1];
	struct timeval	start;

}				t_simulation_data;

t_simulation_data simulation;

void    		simulation_end(t_simulation_data *simulation);
unsigned long	elapsed_time(struct timeval t1, struct timeval t2);
void			message(int n, int state);
int				simulation_init(t_simulation_data *sim, int ac, char **av);
size_t			ft_strlen(const char *s);
int				ft_atoi(const char *str);

#endif
