FLAGS = -Wall -Wextra -Werror

SRCS = ft_atoi.c ft_strlen.c simulation_init.c message.c elapsed_time.c simulation_delete.c 

HEADER = philosophers.h

OBJS = $(SRCS:.c=.o)

NAME = philo_two

$(NAME): $(HEADER) $(SRCS) main_philo_two.c
		gcc $(FLAGS) $(SRCS) main_philo_two.c -o $(NAME) -lpthread

all: $(PHILO1)

clean:
		rm -f $(OBJS)

fclean: clean
		rm -f $(NAME)

re: fclean all

norme:
	norminette $(SRCS) $(HEADER)
