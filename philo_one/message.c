// 42 Header

#include "philosophers.h"

static void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t				i;
	unsigned char		*cdest;
	const unsigned char	*csrc;

	if (!dest && !src)
		return (dest);
	cdest = dest;
	csrc = src;
	i = 0;
	if (dest <= src)
		while (i < n)
		{
			cdest[i] = csrc[i];
			i++;
		}
	else
		while (n > 0)
		{
			cdest[n - 1] = csrc[n - 1];
			n--;
		}
	return (dest);
}

static int    ft_itoa(int n, char *str) // renvoie le nombre d'octets écris
{                                                                                
	int i;
	int j;
	char t[10];

	memset(t, 48, 10);
	i = 9;
	while (n)
	{
		t[i] = (n % 10) + 48; 
		n = n / 10;
		i--;
	}
	i = 0;
	while (i < 10 && t[i] == 48)
		i++;
	j = 0;
	while (i < 10)
	{
		str[j] = t[i];
		i++;
		j++;
	}
	return (j);
}

static void    ft_ultoa(unsigned long n, char *str)
{
	int i;

	memset(str, 48, 20);
	i = 19;                                                                      
	while (n)
	{
		str[i] = (n % 10) + 48;
		n = n / 10;
		i--;
	}
}

void	message(int n, int state)
{
	struct timeval now;
	static char *strs[] = {
		" has taken a fork\n\0",
		" is eating\n\0",
		" has put down a fork\n\0",
		" is sleeping\n\0",
		" is thinking\n\0",
		" died\n\0"
	};
	char msg[55];
	int len;
	
	gettimeofday(&now, NULL);
	msg[0] = '[';
	ft_ultoa(elapsed_time(simulation.start, now), &msg[1]);
	msg[21] = ']';
	msg[22] = ' ';
	len = ft_itoa(n, &msg[23]);
	ft_memmove(&msg[23 + len], strs[state], ft_strlen(strs[state]) + 1);
	write(1, msg, ft_strlen(msg));
}
