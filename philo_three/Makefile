FLAGS = -Wall -Wextra -Werror

SRCS = 	mini_lft/ft_atoi.c \
		mini_lft/ft_strlen.c \
		mini_lft/ft_strjoin_free.c \
		mini_lft/ft_itoa.c \
		time_utils.c \
		message.c utils.c philosophing.c 

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
