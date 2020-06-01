// 42 Header

#include "philosophers.h"

void	message(int n, int state)
{
	struct timeval now;
	static char *strs[] = {
		"has taken a fork", "is eating", "has put down a fork", "is sleeping", "is thinking", "died"
	};
	
	gettimeofday(&now, NULL);
	printf("[%.20lu] %d %s.\n", 
		elapsed_time(simulation.start, now), n, strs[state]
	);
}
