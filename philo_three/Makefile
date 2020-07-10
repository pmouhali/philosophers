FLAGS = -Wall -Wextra -Werror

SRCS = ft_atoi.c ft_strlen.c message.c elapsed_time.c utils.c philosophing.c 

HEADER = philosophers.h

OBJS = $(SRCS:.c=.o)

NAME = philo_three

$(NAME): $(HEADER) $(SRCS) main.c
		gcc $(FLAGS) $(SRCS) main.c -o $(NAME) -lpthread

all: $(NAME)

clean:
		rm -f $(OBJS)

fclean: clean
		rm -f $(NAME)

re: fclean all

norme:
	norminette $(SRCS) $(HEADER)
