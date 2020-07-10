// 42 Header

#include "philosophers.h"

struct timeval	last_meal;
unsigned int n_meals;
sem_t *forks;
sem_t *death;
sem_t *meals;

int		main(int ac, char *av[])
{
	unsigned int i;
	int *pids;

	if (simulation_init(&simulation, ac, av) || (pids = create_childs(simulation.n_philosophers)) == NULL)
	{
		simulation_delete(NULL);
		return (EXIT_FAILURE);
	}
	sem_wait(death);
	i = -1;
	while (++i < simulation.n_philosophers)
		kill(pids[i], SIGKILL);
	simulation_delete(pids);
	return (EXIT_SUCCESS);
}

/*
**	1. Lancer 1 processus fils par philosphe.	
**	2. Le processus fils obtient son numéro de philosophe.
**		2.1 : Il va vérifier constemment si il est mort (last_meal devient une simple variable). Si il est mort, il POST sur death. 
**		2.2 : Il va lancer un thread avec philosophing comme routine.
**		2.3 : philosophing devra update la variable last meal, et WAIT/POST sur forks.
**
**	3. Si death est débloqué, le main process (father) kill tout les fils.
**	
*/
