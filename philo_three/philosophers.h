// 42 header

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

#include <sys/wait.h> // TO RM

#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>
#include <stdint.h>
#include <sys/time.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <semaphore.h>
#include <sys/types.h>
#include <signal.h>

#include <stdio.h>

#define FALSE 0
#define TRUE  1

#define SEMKEY "/semkey"
#define SEMFORKS "/keyforks"
#define SEMDEATH "/keydeath"
#define THREADS_MAX 10000
#define USAGE "Usage: ./philoX <philosophers> <time to die> <time to eat> <time to sleep> <Optional: how many time each must eat for the simulation to stop>\n"

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
	unsigned int	n_philosophers;                                                
	unsigned char	stop;
	unsigned long	time_to_die;
	unsigned long	time_to_eat;
	unsigned long	time_to_sleep;  
	unsigned int	meals_per_philosopher_before_stop;
	unsigned char	*meals_per_philosopher;
	struct timeval	*philosophers_last_meals;
	struct timeval	start;

}				t_simulation_data;

t_simulation_data simulation;
struct timeval last_meal;
sem_t *forks;
sem_t *death;

int		*create_childs(unsigned int n);
void	child_process_actions(unsigned int n);
unsigned long	elapsed_time(struct timeval t1, struct timeval t2);
void			message(int n, int state);
int     simulation_init(t_simulation_data *sim, int ac, char **av);
size_t	ft_strlen(const char *s);
int	ft_atoi(const char *str);
void simulation_delete(void *t1, sem_t *forks, sem_t *death);
void    create_threads(pthread_t *threads_ids, int *philosopher_ids);
void    *philosophing(void *arg);
void    wait_threads(pthread_t *thread_ids);
void		end_checker(void);

#endif
