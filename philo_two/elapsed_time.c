// 42 Header

#include "philosophers.h"

/*
**	[NAME] 
**
**	elapsed_time
**
**	[DESCRIPTION]
**	
**	Returns the time interval in milliseconds between t1 and t2.
**
**	t1 and t2 are struct timeval variables obtained by calling the <sys/times.h>
**	function gettimeofday()
**
*/

unsigned long	elapsed_time(struct timeval t1, struct timeval t2)
{
	unsigned long timestamp1;
	unsigned long timestamp2;

	timestamp1 = (t1.tv_usec / 1000 + t1.tv_sec * 1000);
	timestamp2 = (t2.tv_usec / 1000 + t2.tv_sec * 1000);
	if (timestamp1 >= timestamp2)
		return (0);
	return (timestamp2 - timestamp1);
}
