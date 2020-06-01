FLAGS = -Wall -Wextra -Werror

SRCS = ft_strlen.c simulation_init.c message.c elapsed_time.c 

HEADER = philosophers.h

OBJS = $(SRCS:.c=.o)

PHILO1 = philo_one
PHILO2 = philo_two
PHILO3 = philo_three

$(PHILO1): $(HEADER) $(SRCS) main_philo_one.c
		gcc $(FLAGS) $(SRCS) main_philo_one.c -o $(PHILO1) -lpthread

all: $(PHILO1)

clean:
		rm -f $(OBJS)

fclean: clean
		rm -f $(NAME)

re: fclean all

norme:
	norminette $(SRCS) $(HEADER)
