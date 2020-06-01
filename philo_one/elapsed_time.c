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
	unsigned long e;

	e = (t2.tv_sec - t1.tv_sec) * 1000;
	e += (t2.tv_usec - t1.tv_usec) / 1000;
	return (e);
}
