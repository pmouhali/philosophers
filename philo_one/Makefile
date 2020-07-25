FLAGS = -Wall -Wextra -Werror

SRCS = ft_atoi.c ft_strlen.c simulation_tools.c message.c elapsed_time.c fcn_forks.c watch_for_death.c 

HEADER = philosophers.h

OBJS = $(SRCS:.c=.o)

NAME = philo_one

$(NAME): $(HEADER) $(SRCS) main.c
		gcc $(FLAGS) -o1 $(SRCS) main.c -o $(NAME) -lpthread

all: $(NAME)

clean:
		rm -f $(OBJS)

fclean: clean
		rm -f $(NAME)

re: fclean all

norme:
	norminette $(SRCS) $(HEADER)
