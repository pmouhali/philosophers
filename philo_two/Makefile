FLAGS = -Wall -Wextra -Werror

SRCS =	mini_lft/ft_strlen.c \
		mini_lft/ft_strjoin_free.c \
		mini_lft/ft_atoi.c \
		mini_lft/ft_itoa.c \
		message.c \
		time_utils.c \
		simulation_utils.c \
		thread_utils.c \
		philosophing_routine.c

HEADER = philosophers.h

OBJS = $(SRCS:.c=.o)

NAME = philo_two

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
