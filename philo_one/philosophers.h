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
	int				n_philosophers;                                                
	int				forks;                                                
	unsigned char			*table;
	unsigned char				stop;
	unsigned long	time_to_die;
	unsigned long	time_to_eat;
	unsigned long	time_to_sleep;  
	int				meals_per_philosopher_before_stop;
	unsigned char			*meals_per_philosopher;
	struct timeval	start;

}				t_simulation_data;

t_simulation_data simulation;

unsigned long	elapsed_time(struct timeval t1, struct timeval t2);
void			message(int n, int state);
int     simulation_init(t_simulation_data *sim, int ac, char **av);
size_t	ft_strlen(const char *s);
int	ft_atoi(const char *str);

#endif
