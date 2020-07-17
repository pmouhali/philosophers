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

#define SEMFORKS "/keyforks"
#define SEMDEATH "/keydeath"
#define SEMMEALS "/keymeals"
#define THREADS_MAX 10000
#define USAGE "Usage: ./philo_three <philosophers> <time to die> <time to eat> <time to sleep> <Optional: how many time each must eat for the simulation to stop>\n"

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
	unsigned int	meals_option;
	struct timeval	start;

}				t_simulation_data;

t_simulation_data simulation;
struct timeval last_meal;
unsigned int n_meals;
sem_t *forks;
sem_t *death;
sem_t *meals;

int				*create_childs(unsigned int n);
void			child_process_actions(unsigned int n);
unsigned long	elapsed_time(struct timeval t1, struct timeval t2);
void			message(int n, int state);
int				simulation_init(t_simulation_data *sim, int ac, char **av);
size_t			ft_strlen(const char *s);
int				ft_atoi(const char *str);
void			simulation_delete(void *t1);
void			create_threads(pthread_t *threads_ids, int *philosopher_ids);
void			*philosophing(void *arg);
void			*count_meals_routine(void *arg);
void			wait_threads(pthread_t *thread_ids);
void			end_checker(void);

#endif
